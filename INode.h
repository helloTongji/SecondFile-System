#ifndef INODE_H
#define INODE_H

#include "Buffer.h"

class Inode {
public:
    enum INodeFlag {
        IUPD = 0x2,
        IACC = 0x4,
    };

    static const unsigned int IALLOC = 0x8000;
    static const unsigned int IFMT = 0x6000;
    static const unsigned int IFDIR = 0x4000;
    static const unsigned int IFBLK = 0x6000;
    static const unsigned int ILARG = 0x1000;
    static const unsigned int IREAD = 0x100;
    static const unsigned int IWRITE = 0x80;
    static const unsigned int IEXEC = 0x40;
    static const unsigned int IRWXU = (IREAD | IWRITE | IEXEC);
    static const unsigned int IRWXG = ((IRWXU) >> 3);
    static const unsigned int IRWXO = ((IRWXU) >> 6);

    static const int BLOCK_SIZE = 512;
    static const int ADDRESS_PER_INDEX_BLOCK = BLOCK_SIZE / sizeof(int);
    static const int LARGE_FILE_BLOCK = 128 * 2 + 6;
    static const int HUGE_FILE_BLOCK = 128 * 128 * 2 + 128 * 2 + 6;

public:
    unsigned int i_flag;
    unsigned int i_mode;
    int		i_count;
    int		i_nlink;
    short	i_dev;
    int		i_number;
    short	i_uid;
    short	i_gid;
    int		i_size;
    int		i_addr[10];
    int		i_lastr;
public:
    Inode();
    ~Inode();
    void ReadI();
    void WriteI();
    int Bmap(int lbn);
    void IUpdate(int time);
    void ITrunc();
    void Clean();
    void ICopy(Buffer* bp, int inumber);
};
class DiskINode {
public:
    unsigned int d_mode;
    int		d_nlink;
    short	d_uid;
    short	d_gid;
    int		d_size;
    int		d_addr[10];
    int		d_atime;
    int		d_mtime;
public:
    DiskINode();
    ~DiskINode();
};

#endif
