#include "Utility.h"
#include "FileManager.h"
#include "BufferManager.h"
#include "User.h"
#include<QDebug>
FileManager::FileManager() {
    m_FileSystem = &g_FileSystem;
    openFileTable = &g_OpenFileTable;
    inodeTable = &g_INodeTable;
    rootDirINode = inodeTable->IGet(FileSystem::ROOT_INODE_NO);
    rootDirINode->i_count += 0xff;
}

FileManager::~FileManager() {

}
void FileManager::Open() {
    User &u = g_User;
    Inode* pINode;
    pINode = this->NameI(FileManager::OPEN);
    if (NULL == pINode) {
        return;
    }
    this->Open1(pINode, u.arg[1], 0);
}

void FileManager::Creat() {
    Inode* pINode;
    User& u = g_User;
    unsigned int newACCMode = u.arg[1];
    pINode = this->NameI(FileManager::CREATE);
    if (NULL == pINode) {
        if (u.u_error)
            return;
        pINode = this->MakNode(newACCMode);
        if (NULL == pINode)
            return;
        this->Open1(pINode, File::FWRITE, 2);
        return;
    }
    this->Open1(pINode, File::FWRITE, 1);
    pINode->i_mode |= newACCMode;
}
Inode* FileManager::NameI(enum DirectorySearchMode mode) {
    BufferManager& bufferManager = g_BufferManager;
    User &u = g_User;
    Inode* pINode = u.cdir;
    Buffer* pBuffer;
    int freeEntryOffset;
    unsigned int index = 0, nindex = 0;

    if ('/' == u.dirp[0]) {
        nindex = ++index + 1;
        pINode = this->rootDirINode;
    }
    while (1) {
        if (u.u_error != 0) {
            break;
        }
        if (nindex >= u.dirp.length()) {
            return pINode;
        }
        if ((pINode->i_mode&Inode::IFMT) != Inode::IFDIR) {
            u.u_error = 20;
            break;
        }

        nindex = u.dirp.find_first_of('/', index);
        Utility::memset(u.dbuf, 0, sizeof(u.dbuf));
        Utility::memcpy(u.dbuf, u.dirp.data() + index, (nindex == (unsigned int)string::npos ? u.dirp.length() : nindex) - index);
        index = nindex + 1;
        u.IOParam.offset = 0;
        u.IOParam.count = pINode->i_size / sizeof(DirectoryEntry);
        freeEntryOffset = 0;
        pBuffer = NULL;

        while (1) {

            if (0 == u.IOParam.count) {
                if (NULL != pBuffer) {
                    bufferManager.Brelse(pBuffer);
                }
                if (FileManager::CREATE == mode && nindex >= u.dirp.length()) {
                    u.pdir = pINode;
                    if (freeEntryOffset) {
                        u.IOParam.offset = freeEntryOffset - sizeof(DirectoryEntry);
                    }
                    else {
                        pINode->i_flag |= Inode::IUPD;
                    }
                    return NULL;
                }
                u.u_error = 2;
                goto out;
            }

            if (0 == u.IOParam.offset%Inode::BLOCK_SIZE) {
                if (pBuffer) {
                    bufferManager.Brelse(pBuffer);
                }
                int phyBlkno = pINode->Bmap(u.IOParam.offset / Inode::BLOCK_SIZE);
                pBuffer = bufferManager.Bread(phyBlkno);
            }

            Utility::memcpy(&u.dent, pBuffer->addr + (u.IOParam.offset % Inode::BLOCK_SIZE), sizeof(u.dent));
            u.IOParam.offset += sizeof(DirectoryEntry);
            u.IOParam.count--;

            if (0 == u.dent.m_ino) {
                if (0 == freeEntryOffset) {
                    freeEntryOffset = u.IOParam.offset;
                }
                continue;
            }

            if (!Utility::memcmp(u.dbuf, &u.dent.name, sizeof(DirectoryEntry) - 4)) {
                break;
            }
        }

        if (pBuffer) {
            bufferManager.Brelse(pBuffer);
        }

        if (FileManager::DELETE == mode && nindex >= u.dirp.length()) {
            return pINode;
        }

        this->inodeTable->IPut(pINode);
        pINode = this->inodeTable->IGet(u.dent.m_ino);

        if (NULL == pINode) {
            return NULL;
        }
    }

out:
    this->inodeTable->IPut(pINode);
    return NULL;
}
void FileManager::Open1(Inode* pINode, int mode, int trf) {
    User& u = g_User;
    if (1 == trf) {
        pINode->ITrunc();
    }
    File* pFile = this->openFileTable->FAlloc();
    if (NULL == pFile) {
        this->inodeTable->IPut(pINode);
        return;
    }
    pFile->flag = mode & (File::FREAD | File::FWRITE);
    pFile->inode = pINode;
    if (u.u_error == 0) {
        return;
    }
    else {
        int fd = u.ar0[0];
        if (fd != -1) {
            u.ofiles.SetF(fd, NULL);
            pFile->count--;
        }
        this->inodeTable->IPut(pINode);
    }
}
Inode* FileManager::MakNode(unsigned int mode) {
    Inode* pINode;
    pINode = this->m_FileSystem->IAlloc();
    if (NULL == pINode) {
        return NULL;
    }

    pINode->i_flag |= (Inode::IACC | Inode::IUPD);
    pINode->i_mode = mode | Inode::IALLOC;
    pINode->i_nlink = 1;
    this->WriteDir(pINode);
    return pINode;
}
void FileManager::WriteDir(Inode* pINode) {
    User& u = g_User;
    u.dent.m_ino = pINode->i_number;
    Utility::memcpy(u.dent.name, u.dbuf, DirectoryEntry::DIRSIZ);

    u.IOParam.count = DirectoryEntry::DIRSIZ + 4;
    u.IOParam.base = (unsigned char *)&u.dent;
    u.pdir->WriteI();
    this->inodeTable->IPut(u.pdir);
}

void FileManager::Close() {
    User& u = g_User;
    int fd = u.arg[0];
    File* pFile = u.ofiles.GetF(fd);
    if (NULL == pFile) {
        return;
    }
    u.ofiles.SetF(fd, NULL);
    this->openFileTable->CloseF(pFile);
}

void FileManager::UnLink() {
    Inode* pINode;
    Inode* pDeleteINode;
    User& u = g_User;

    pDeleteINode = this->NameI(FileManager::DELETE);
    if (NULL == pDeleteINode) {
        return;
    }

    pINode = this->inodeTable->IGet(u.dent.m_ino);
    if (NULL == pINode) {
        return;
    }
    u.IOParam.offset -= (DirectoryEntry::DIRSIZ + 4);
    u.IOParam.base = (unsigned char *)&u.dent;
    u.IOParam.count = DirectoryEntry::DIRSIZ + 4;

    u.dent.m_ino = 0;
    pDeleteINode->WriteI();
    pINode->i_nlink--;
    pINode->i_flag |= Inode::IUPD;

    this->inodeTable->IPut(pDeleteINode);
    this->inodeTable->IPut(pINode);
}

void FileManager::Seek() {
    File* pFile;
    User& u = g_User;
    int fd = u.arg[0];

    pFile = u.ofiles.GetF(fd);
    if (NULL == pFile) {
        return;
    }

    int offset = u.arg[1];

    switch (u.arg[2]) {
    case 0:
        pFile->offset = offset;
        break;
    case 1:
        pFile->offset += offset;
        break;
    case 2:
        pFile->offset = pFile->inode->i_size + offset;
        break;
    default:
        QString inputStr=" 参数origin ";
        inputStr=inputStr+QString::number(u.arg[2])+" 未定义 ! \n";
        g_Cmd->append(inputStr);
        break;
    }
}

void FileManager::read() {
    this->Rdwr(File::FREAD);
}

void FileManager::Write() {
    this->Rdwr(File::FWRITE);
}

void FileManager::Rdwr(enum File::FileFlags mode) {
    File* pFile;
    User& u = g_User;
    pFile = u.ofiles.GetF(u.arg[0]);
    if (NULL == pFile) {
        return;
    }
    if ((pFile->flag & mode) == 0) {
        u.u_error = 13;
        return;
    }

    u.IOParam.base = (unsigned char *)u.arg[1];
    u.IOParam.count = u.arg[2];

    u.IOParam.offset = pFile->offset;
    if (File::FREAD == mode) {
        pFile->inode->ReadI();
    }
    else {
        pFile->inode->WriteI();
    }
    pFile->offset += (u.arg[2] - u.IOParam.count);
    u.ar0[0] = u.arg[2] - u.IOParam.count;
}

void FileManager::Ls() {
    User &u = g_User;
    BufferManager& bufferManager = g_BufferManager;

    Inode* pINode = u.cdir;
    Buffer* pBuffer = NULL;
    u.IOParam.offset = 0;
    u.IOParam.count = pINode->i_size / sizeof(DirectoryEntry);

    while (u.IOParam.count) {
        if (0 == u.IOParam.offset%Inode::BLOCK_SIZE) {
            if (pBuffer) {
                bufferManager.Brelse(pBuffer);
            }
            int phyBlkno = pINode->Bmap(u.IOParam.offset / Inode::BLOCK_SIZE);
            pBuffer = bufferManager.Bread(phyBlkno);
        }
        Utility::memcpy(&u.dent, pBuffer->addr+ (u.IOParam.offset % Inode::BLOCK_SIZE), sizeof(u.dent));
        u.IOParam.offset += sizeof(DirectoryEntry);
        u.IOParam.count--;

        if (0 == u.dent.m_ino)
            continue;
        u.ls += u.dent.name;
        u.ls += "\n";
    }

    if (pBuffer) {
        bufferManager.Brelse(pBuffer);
    }
}
void FileManager::ChDir() {
    Inode* pINode;
    User& u = g_User;

    pINode = this->NameI(FileManager::OPEN);
    if (NULL == pINode) {
        return;
    }
    if ((pINode->i_mode & Inode::IFMT) != Inode::IFDIR) {
        u.u_error = 20;
        this->inodeTable->IPut(pINode);
        return;
    }

    u.cdir = pINode;
    if (u.dirp[0] != '/') {
        u.curDirPath += u.dirp;
    }
    else {
        u.curDirPath = u.dirp;
    }
    if (u.curDirPath.back() != '/')
        u.curDirPath.push_back('/');
}
