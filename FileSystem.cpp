#include "Utility.h"
#include "FileSystem.h"
#include "User.h"
#include<QDebug>
FileSystem::FileSystem() {
    deviceDriver = &g_DeviceDriver;
    superBlock = &g_SuperBlock;
    bufferManager = &g_BufferManager;

    if (!deviceDriver->Exists()) {
        FormatDevice();
    }
    else {
        LoadSuperBlock();
    }
}

FileSystem::~FileSystem() {
    Update();
    deviceDriver = NULL;
    superBlock = NULL;
}
void FileSystem::FormatSuperBlock() {
    superBlock->s_isize = FileSystem::INODE_ZONE_SIZE;
    superBlock->s_fsize = FileSystem::DISK_SIZE;
    superBlock->s_nfree = 0;
    superBlock->s_free[0] = -1;
    superBlock->s_ninode = 0;
    superBlock->s_flock = 0;
    superBlock->s_ilock = 0;
    superBlock->s_fmod = 0;
    superBlock->s_ronly = 0;
    time((time_t*)&superBlock->s_time);
}
void FileSystem::FormatDevice() {
    FormatSuperBlock();
    deviceDriver->Construct();
    deviceDriver->write(superBlock, sizeof(SuperBlock), 0);

    DiskINode emptyDINode, rootDINode;
    rootDINode.d_mode |= Inode::IALLOC | Inode::IFDIR;
    rootDINode.d_nlink = 1;
    deviceDriver->write(&rootDINode, sizeof(rootDINode));
    for (int i = 1; i < FileSystem::INode_NUMBERS; ++i) {
        if (superBlock->s_ninode < SuperBlock::MAX_NINODE) {
            superBlock->s_inode[superBlock->s_ninode++] = i;
        }
        deviceDriver->write(&emptyDINode, sizeof(emptyDINode));
    }
    char freeBlock[BLOCK_SIZE], freeBlock1[BLOCK_SIZE];
    memset(freeBlock, 0, BLOCK_SIZE);
    memset(freeBlock1, 0, BLOCK_SIZE);

    for (int i = 0; i < FileSystem::DATA_ZONE_SIZE; ++i) {
        if (superBlock->s_nfree >= SuperBlock::MAX_NFREE) {
            memcpy(freeBlock1, &superBlock->s_nfree, sizeof(int) + sizeof(superBlock->s_free));
            deviceDriver->write(&freeBlock1, BLOCK_SIZE);
            superBlock->s_nfree = 0;
        }
        else {
            deviceDriver->write(freeBlock, BLOCK_SIZE);
        }
        superBlock->s_free[superBlock->s_nfree++] = i + DATA_ZONE_START_SECTOR;
    }

    time((time_t*)&superBlock->s_time);
    deviceDriver->write(superBlock, sizeof(SuperBlock), 0);
}
void FileSystem::LoadSuperBlock() {
    deviceDriver->read(superBlock, sizeof(SuperBlock), SUPERBLOCK_START_SECTOR*BLOCK_SIZE);
}
void FileSystem::Update() {
    Buffer* pBuffer;
    superBlock->s_fmod = 0;
    superBlock->s_time = (int)Utility::time(NULL);
    for (int j = 0; j < 2; j++) {
        int* p = (int *)superBlock + j * 128;
        pBuffer = this->bufferManager->GetBlk(FileSystem::SUPERBLOCK_START_SECTOR + j);
        Utility::memcpy(pBuffer->addr, p, BLOCK_SIZE);
        this->bufferManager->Bwrite(pBuffer);
    }
    g_INodeTable.UpdateInodeTable();
    this->bufferManager->Bflush();
}
Buffer* FileSystem::Alloc() {
    int blkno;
    Buffer* pBuffer;
    User& u = g_User;
    blkno = superBlock->s_free[--superBlock->s_nfree];

//    QString inputStr="blockNo";
//    inputStr=inputStr+QString::number(superBlock->s_free[superBlock->s_nfree]);
//    g_Cmd->append(inputStr);
    if (blkno <= 0) {
        superBlock->s_nfree = 0;
        u.u_error = 28;
        return NULL;
    }
    if (superBlock->s_nfree <= 0) {
        pBuffer = this->bufferManager->Bread(blkno);
        int* p = (int *)pBuffer->addr;
        superBlock->s_nfree = *p++;
        memcpy(superBlock->s_free, p, sizeof(superBlock->s_free));
        this->bufferManager->Brelse(pBuffer);
    }
    pBuffer = this->bufferManager->GetBlk(blkno);
    if (pBuffer) {
        this->bufferManager->Bclear(pBuffer);
    }
    superBlock->s_fmod = 1;
    return pBuffer;
}
Inode* FileSystem::IAlloc() {
    Buffer* pBuffer;
    Inode* pINode;
    User& u = g_User;
    int ino;
    if (superBlock->s_ninode <= 0) {
        ino = -1;
        for (int i = 0; i < superBlock->s_isize; ++i) {
            pBuffer = this->bufferManager->Bread(FileSystem::INODE_ZONE_START_SECTOR + i);
            int* p = (int*)pBuffer->addr;
            for (int j = 0; j < FileSystem::INODE_NUMBER_PER_SECTOR; ++j) {
                ++ino;
                int mode = *(p + j * sizeof(DiskINode) / sizeof(int));
                if (mode) {
                    continue;
                }
                if (g_INodeTable.IsLoaded(ino) == -1) {
                    superBlock->s_inode[superBlock->s_ninode++] = ino;
                    if (superBlock->s_ninode >= SuperBlock::MAX_NINODE) {
                        break;
                    }
                }
            }

            this->bufferManager->Brelse(pBuffer);
            if (superBlock->s_ninode >= SuperBlock::MAX_NINODE) {
                break;
            }
        }
        if (superBlock->s_ninode <= 0) {
            u.u_error = 28;
            return NULL;
        }
    }

    ino = superBlock->s_inode[--superBlock->s_ninode];
    pINode = g_INodeTable.IGet(ino);
    if (NULL == pINode) {
        QString inputStr="无空闲内存INode\n";
        g_Cmd->append(inputStr);
        return NULL;
    }

    pINode->Clean();
    superBlock->s_fmod = 1;
    return pINode;
}
void FileSystem::IFree(int number) {
    if (superBlock->s_ninode >= SuperBlock::MAX_NINODE) {
        return ;
    }
    superBlock->s_inode[superBlock->s_ninode++] = number;
    superBlock->s_fmod = 1;
}
void FileSystem::Free(int blkno) {
    Buffer* pBuffer;
    User& u = g_User;

    if (superBlock->s_nfree >=SuperBlock::MAX_NFREE ) {
        pBuffer = this->bufferManager->GetBlk(blkno);
        int *p = (int*)pBuffer->addr;
        *p++ = superBlock->s_nfree;
        Utility::memcpy(p, superBlock->s_free, sizeof(int)*SuperBlock::MAX_NFREE);
        superBlock->s_nfree = 0;
        this->bufferManager->Bwrite(pBuffer);
    }

    superBlock->s_free[superBlock->s_nfree++] = blkno;
    superBlock->s_fmod = 1;
}
