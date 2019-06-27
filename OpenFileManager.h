#ifndef OPENFILEMANAGER_H
#define OPENFILEMANAGER_H
/*
 * 打开文件管理类(OpenFileManager)负责
 * 内核中对打开文件机构的管理，为进程
 * 打开文件建立内核数据结构之间的勾连
 * 关系。
 * 勾连关系指进程u区中打开文件描述符指向
 * 打开文件表中的File打开文件控制结构，
 * 以及从File结构指向文件对应的内存Inode。
 */
#include "File.h"
#include "FileSystem.h"
class OpenFileTable {
public:
    static const int NFILE = 100;
public:
    File m_File[NFILE];

public:
    OpenFileTable();
    ~OpenFileTable();

    // /*
     // * @comment 根据用户系统调用提供的文件描述符参数fd，
     // * 找到对应的打开文件控制块File结构
     // */
    // File* GetF(int fd);
    /*
     * @comment 在系统打开文件表中分配一个空闲的File结构
     */
    File* FAlloc();
    void CloseF(File* pFile);
    void Format();
};
class InodeTable {
public:
    static const int NINODE = 100;

private:
    Inode m_Inode[NINODE];
    FileSystem* m_FileSystem;
public:
    InodeTable();
    ~InodeTable();
    Inode* IGet(int inumber);
    void IPut(Inode* pNode);
    void UpdateInodeTable();
    int IsLoaded(int inumber);
    Inode* GetFreeInode();
    void Format();
};
#endif
