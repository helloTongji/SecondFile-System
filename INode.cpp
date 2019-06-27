#include "Utility.h"
#include "Inode.h"
#include "FileSystem.h"
#include "User.h"
DiskINode::DiskINode() {
    this->d_mode = 0;
    this->d_nlink = 0;
    this->d_uid = -1;
    this->d_gid = -1;
    this->d_size = 0;
    Utility::memset(d_addr, 0, sizeof(d_addr));
    this->d_atime = 0;
    this->d_mtime = 0;
}

DiskINode::~DiskINode() {
}

Inode::Inode() {
    this->i_flag = 0;
    this->i_mode = 0;
    this->i_count = 0;
    this->i_nlink = 0;
    this->i_number = -1;
    this->i_uid = -1;
    this->i_gid = -1;
    this->i_size = 0;
    this->i_lastr = -1;
    Utility::memset(i_addr, 0, sizeof(i_addr));
}

Inode::~Inode() {
}
void Inode::ReadI() {
    User& u = g_User;
    BufferManager& bufferManager = g_BufferManager;
    int lbn, bn;
    int offset, nbytes;
    Buffer* pBuffer;
    if (0 == u.IOParam.count) {
        return;
    }
    this->i_flag |= Inode::IACC;

    while (0 == u.u_error && u.IOParam.count) {
        lbn = bn = u.IOParam.offset / Inode::BLOCK_SIZE;
        offset = u.IOParam.offset % Inode::BLOCK_SIZE;
        nbytes = Utility::min(Inode::BLOCK_SIZE - offset, u.IOParam.count);
        int remain = this->i_size - u.IOParam.offset;
        if (remain <= 0) {
            return;
        }
        nbytes = Utility::min(nbytes, remain);
        if ((bn = this->Bmap(lbn)) == 0) {
            return;
        }

        pBuffer = bufferManager.Bread(bn);
        this->i_lastr = lbn;
        unsigned char* start = pBuffer->addr + offset;
        Utility::memcpy(u.IOParam.base, start, nbytes);
        u.IOParam.base += nbytes;
        u.IOParam.offset += nbytes;
        u.IOParam.count -= nbytes;

        bufferManager.Brelse(pBuffer);
    }
}
void Inode::WriteI() {
    int lbn, bn;
    int offset, nbytes;
    Buffer* pBuffer;
    User& u = g_User;
    BufferManager& bufferManager = g_BufferManager;

    this->i_flag |= (Inode::IACC | Inode::IUPD);
    if (0 == u.IOParam.count) {
        return;
    }

    while (0 == u.u_error && u.IOParam.count) {
        lbn = u.IOParam.offset / Inode::BLOCK_SIZE;
        offset = u.IOParam.offset % Inode::BLOCK_SIZE;
        nbytes = Utility::min(Inode::BLOCK_SIZE - offset, u.IOParam.count);
        if ((bn = this->Bmap(lbn)) == 0) {
            return;
        }

        if (Inode::BLOCK_SIZE == nbytes) {
            pBuffer = bufferManager.GetBlk(bn);
        }
        else {
            pBuffer = bufferManager.Bread(bn);
        }
        unsigned char* start = pBuffer->addr + offset;
        Utility::memcpy(start, u.IOParam.base, nbytes);
        u.IOParam.base += nbytes;
        u.IOParam.offset += nbytes;
        u.IOParam.count -= nbytes;

        if (u.u_error != 0) {
            bufferManager.Brelse(pBuffer);
        }
        bufferManager.Bdwrite(pBuffer);
        if (this->i_size < u.IOParam.offset) {
            this->i_size = u.IOParam.offset;
        }
        this->i_flag |= Inode::IUPD;
    }
}
void Inode::ICopy(Buffer* pb, int inumber) {
    DiskINode& dINode = *(DiskINode*)(pb->addr + (inumber%FileSystem::INODE_NUMBER_PER_SECTOR)*sizeof(DiskINode));
    i_mode = dINode.d_mode;
    i_nlink = dINode.d_nlink;
    i_uid = dINode.d_uid;
    i_gid = dINode.d_gid;
    i_size = dINode.d_size;
    Utility::memcpy(i_addr, dINode.d_addr, sizeof(i_addr));
}
int Inode::Bmap(int lbn) {
    User& u = g_User;
    BufferManager& bufferManager = g_BufferManager;
    FileSystem& m_FileSystem = g_FileSystem;
    Buffer* pFirstBuffer, *pSecondBuffer;
    int phyBlkno, index;
    int *iTable;

    if (lbn >= Inode::HUGE_FILE_BLOCK) {
        u.u_error = 27;
        return 0;
    }
    if (lbn < 6) {
        phyBlkno = this->i_addr[lbn];
        if (phyBlkno == 0 && (pFirstBuffer = m_FileSystem.Alloc()) != NULL) {
            phyBlkno = pFirstBuffer->blkno;
            bufferManager.Bdwrite(pFirstBuffer);
            this->i_addr[lbn] = phyBlkno;
            this->i_flag |= Inode::IUPD;
        }
        return phyBlkno;
    }
    if (lbn < Inode::LARGE_FILE_BLOCK) {
        index = (lbn - 6) / Inode::ADDRESS_PER_INDEX_BLOCK + 6;
    }
    else {
        index = (lbn - Inode::LARGE_FILE_BLOCK) / (Inode::ADDRESS_PER_INDEX_BLOCK * Inode::ADDRESS_PER_INDEX_BLOCK) + 8;
    }

    phyBlkno = this->i_addr[index];
    if (phyBlkno) {
        pFirstBuffer = bufferManager.Bread(phyBlkno);
    }
    else {
        this->i_flag |= Inode::IUPD;
        if ((pFirstBuffer = m_FileSystem.Alloc()) == 0) {
            return 0;
        }
        this->i_addr[index] = pFirstBuffer->blkno;
    }

    iTable = (int *)pFirstBuffer->addr;
    if (index >= 8) {
        index = ((lbn - Inode::LARGE_FILE_BLOCK) / Inode::ADDRESS_PER_INDEX_BLOCK) % Inode::ADDRESS_PER_INDEX_BLOCK;
        phyBlkno = iTable[index];

        if (phyBlkno) {
            bufferManager.Brelse(pFirstBuffer);
            pSecondBuffer = bufferManager.Bread(phyBlkno);
        }
        else {
            if ((pSecondBuffer = m_FileSystem.Alloc()) == NULL) {
                bufferManager.Brelse(pFirstBuffer);
                return 0;
            }
            iTable[index] = pSecondBuffer->blkno;
            bufferManager.Bdwrite(pFirstBuffer);
        }

        pFirstBuffer = pSecondBuffer;
        iTable = (int *)pSecondBuffer->addr;
    }

    if (lbn < Inode::LARGE_FILE_BLOCK) {
        index = (lbn - 6) % Inode::ADDRESS_PER_INDEX_BLOCK;
    }
    else {
        index = (lbn - Inode::LARGE_FILE_BLOCK) % Inode::ADDRESS_PER_INDEX_BLOCK;
    }

    if ((phyBlkno = iTable[index]) == 0 && (pSecondBuffer = m_FileSystem.Alloc()) != NULL) {
        phyBlkno = pSecondBuffer->blkno;
        iTable[index] = phyBlkno;
        bufferManager.Bdwrite(pSecondBuffer);
        bufferManager.Bdwrite(pFirstBuffer);
    }
    else {
        bufferManager.Brelse(pFirstBuffer);
    }
    return phyBlkno;
}

void Inode::Clean() {
    this->i_mode = 0;
    this->i_nlink = 0;
    this->i_uid = -1;
    this->i_gid = -1;
    this->i_size = 0;
    this->i_lastr = -1;
    Utility::memset(i_addr, 0, sizeof(i_addr));
}
void Inode::IUpdate(int time) {
    Buffer* pBuffer;
    DiskINode dINode;
    FileSystem& m_FileSystem = g_FileSystem;
    BufferManager& bufferManager = g_BufferManager;
    if (this->i_flag&(Inode::IUPD | Inode::IACC)) {
        pBuffer = bufferManager.Bread(FileSystem::INODE_ZONE_START_SECTOR + this->i_number / FileSystem::INODE_NUMBER_PER_SECTOR);
        dINode.d_mode = this->i_mode;
        dINode.d_nlink = this->i_nlink;
        dINode.d_uid = this->i_uid;
        dINode.d_gid = this->i_gid;
        dINode.d_size = this->i_size;
        memcpy(dINode.d_addr, i_addr, sizeof(dINode.d_addr));
        if (this->i_flag & Inode::IACC) {
            dINode.d_atime = time;
        }
        if (this->i_flag & Inode::IUPD) {
            dINode.d_mtime = time;
        }

        unsigned char* p = pBuffer->addr + (this->i_number % FileSystem::INODE_NUMBER_PER_SECTOR) * sizeof(DiskINode);
        DiskINode* pNode = &dINode;
        Utility::memcpy(p, pNode, sizeof(DiskINode));
        bufferManager.Bwrite(pBuffer);
    }
}

void Inode::ITrunc() {
    BufferManager &bufferManager = g_BufferManager;
    FileSystem& m_FileSystem = g_FileSystem;
    Buffer* pFirstBuffer, *pSecondBuffer;

    for (int i = 9; i >= 0; --i) {
        if (this->i_addr[i]) {
            if (i >= 6) {
                pFirstBuffer = bufferManager.Bread(this->i_addr[i]);
                int *pFirst = (int*)pFirstBuffer->addr;
                for (int j = BLOCK_SIZE / sizeof(int) - 1; j >= 0; --j) {
                    if (pFirst[j]) {
                        if (i >= 8) {
                            pSecondBuffer = bufferManager.Bread(pFirst[j]);
                            int* pSecond = (int*)pSecondBuffer->addr;
                            for (int k = BLOCK_SIZE / sizeof(int) - 1; k >= 0; --k) {
                                if (pSecond[k]) {
                                    m_FileSystem.Free(pSecond[k]);
                                }
                            }
                            bufferManager.Brelse(pSecondBuffer);
                        }
                        m_FileSystem.Free(pFirst[j]);
                    }
                }
                bufferManager.Brelse(pFirstBuffer);
            }
            m_FileSystem.Free(this->i_addr[i]);
            this->i_addr[i] = 0;
        }
    }
    this->i_size = 0;
    this->i_flag |= Inode::IUPD;
    this->i_mode &= ~(Inode::ILARG);
    this->i_nlink = 1;
}
