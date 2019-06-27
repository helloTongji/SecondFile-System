#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "Inode.h"
#include "DeviceDriver.h"
#include "BufferManager.h"
class SuperBlock {
public:
    const static int MAX_NFREE = 100;
    const static int MAX_NINODE = 100;
public:
    int	s_isize;
    int	s_fsize;
    int	s_nfree;
    int	s_free[MAX_NFREE];
    int	s_ninode;
    int	s_inode[MAX_NINODE];
    int	s_flock;
    int	s_ilock;
    int	s_fmod;
    int	s_ronly;
    int	s_time;
    int	padding[47];
};

class DirectoryEntry {
public:
    static const int DIRSIZ = 28;
public:
    int m_ino;
    char name[DIRSIZ];
};

class FileSystem {
public:
    static const int BLOCK_SIZE = 512;
    static const int DISK_SIZE = 16384;
    static const int SUPERBLOCK_START_SECTOR = 0;
    static const int INODE_ZONE_START_SECTOR = 2;
    static const int INODE_ZONE_SIZE = 1022;
    static const int INODE_NUMBER_PER_SECTOR = BLOCK_SIZE / sizeof(DiskINode);
    static const int ROOT_INODE_NO = 0;
    static const int INode_NUMBERS = INODE_ZONE_SIZE* INODE_NUMBER_PER_SECTOR;
    static const int DATA_ZONE_START_SECTOR = INODE_ZONE_START_SECTOR + INODE_ZONE_SIZE;
    static const int DATA_ZONE_END_SECTOR = DISK_SIZE - 1;
    static const int DATA_ZONE_SIZE = DISK_SIZE - DATA_ZONE_START_SECTOR;

public:
    DeviceDriver* deviceDriver;
    SuperBlock* superBlock;
    BufferManager* bufferManager;

public:
    FileSystem();
    ~FileSystem();
    void FormatSuperBlock();
    void FormatDevice();
    void LoadSuperBlock();
    void Update();
    Inode* IAlloc();
    void IFree(int number);
    Buffer* Alloc();
    void Free(int blkno);

};

#endif
