#ifndef FILE_H
#define FILE_H
#include "Inode.h"
class File {
public:
    enum FileFlags {
        FREAD = 0x1,
        FWRITE = 0x2,
    };
public:
    File();
    ~File();
    unsigned int flag;
    int		count;
    Inode*	inode;
    int		offset;
};
class OpenFiles {
public:
    static const int NFILE = 100;
private:
    File *processOpenFileTable[NFILE];

public:
    OpenFiles();
    ~OpenFiles();
    int AllocFreeSlot();
    File* GetF(int fd);
    void SetF(int fd, File* pFile);
};
class IOParameter {
public:
    unsigned char* base;
    int offset;
    int count;
};

#endif
