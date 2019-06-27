#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "FileSystem.h"
#include "OpenFileManager.h"
class FileManager
{
public:
    enum DirectorySearchMode
    {
        OPEN = 0,
        CREATE = 1,
        DELETE = 2
    };
public:
    Inode* rootDirINode;
    FileSystem* m_FileSystem;
    InodeTable* inodeTable;
    OpenFileTable* openFileTable;

public:
    FileManager();
    ~FileManager();
    void Open();
    void Creat();
    void Open1(Inode* pINode, int mode, int trf);
    void Close();
    void Seek();
    void read();
    void Write();
    void Rdwr(enum File::FileFlags mode);
    Inode* NameI(enum DirectorySearchMode mode);
    Inode* MakNode(unsigned int mode);
    void UnLink();
    void WriteDir(Inode* pINode);
    void ChDir();
    void Ls();
};

#endif
