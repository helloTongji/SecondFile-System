#include "Utility.h"
#include "OpenFileManager.h"
#include "User.h"
#include<QDebug>
OpenFileTable::OpenFileTable() {
}

OpenFileTable::~OpenFileTable() {
}


void OpenFileTable::Format() {
    File emptyFile;
    for (int i = 0; i < OpenFileTable::NFILE; ++i) {
        Utility::memcpy(m_File + i, &emptyFile, sizeof(File));
    }
}
File* OpenFileTable::FAlloc() {
    User& u = g_User;
    int fd = u.ofiles.AllocFreeSlot();
    if (fd < 0) {
        return NULL;
    }
    for (int i = 0; i < OpenFileTable::NFILE; ++i) {
        if (this->m_File[i].count == 0) {
            u.ofiles.SetF(fd, &this->m_File[i]);
            this->m_File[i].count++;
            this->m_File[i].offset = 0;
            return (&this->m_File[i]);
        }
    }
    u.u_error = 23;
    return NULL;
}
void OpenFileTable::CloseF(File* pFile) {
    pFile->count--;
    if (pFile->count <= 0) {
        g_INodeTable.IPut(pFile->inode);
    }
}

InodeTable::InodeTable() {
    m_FileSystem = &g_FileSystem;
}

InodeTable::~InodeTable() {

}

void InodeTable::Format() {
    Inode emptyINode;
    for (int i = 0; i < InodeTable::NINODE; ++i) {
        Utility::memcpy(m_Inode + i, &emptyINode, sizeof(Inode));
    }
}
int InodeTable::IsLoaded(int inumber) {
    for (int i = 0; i < NINODE; ++i) {
        if (m_Inode[i].i_number == inumber&&m_Inode[i].i_count) {
            return i;
        }
    }
    return -1;
}
Inode* InodeTable::GetFreeInode() {
    for (int i = 0; i < InodeTable::NINODE; i++) {
        if (this->m_Inode[i].i_count == 0) {
            return m_Inode + i;
        }
    }
    return NULL;
}

Inode* InodeTable::IGet(int inumber) {
    Inode* pINode;
    int index = IsLoaded(inumber);
    if (index >= 0) {
        pINode = m_Inode + index;
        ++pINode->i_count;
        return pINode;
    }

    pINode = GetFreeInode();
    if (NULL == pINode) {
        QString inputStr="Inode表溢出，无可用Inode !";
        g_Cmd->append(inputStr);
        g_User.u_error = 23;
        return NULL;
    }

    pINode->i_number = inumber;
    pINode->i_count++;
    BufferManager& bmg = g_BufferManager;
    Buffer* pBuffer = bmg.Bread(FileSystem::INODE_ZONE_START_SECTOR + inumber / FileSystem::INODE_NUMBER_PER_SECTOR);
    pINode->ICopy(pBuffer, inumber);
    bmg.Brelse(pBuffer);
    return pINode;
}
void InodeTable::IPut(Inode* pINode) {
    if (pINode->i_count == 1) {
        if (pINode->i_nlink <= 0) {
            pINode->ITrunc();
            pINode->i_mode = 0;
            this->m_FileSystem->IFree(pINode->i_number);
        }
        pINode->IUpdate((int)Utility::time(NULL));
        pINode->i_flag = 0;
        pINode->i_number = -1;
    }

    pINode->i_count--;
}
void InodeTable::UpdateInodeTable() {
    for (int i = 0; i < InodeTable::NINODE; ++i) {
        if (this->m_Inode[i].i_count) {
            this->m_Inode[i].IUpdate((int)Utility::time(NULL));
        }
    }
}
