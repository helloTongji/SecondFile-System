#ifndef  USER_H
#define USER_H
/*
 * @comment 该类与Unixv6中 struct user结构对应，因此只改变
 * 类名，不修改成员结构名字，关于数据类型的对应关系如下:
 */
#include "FileManager.h"
#include <string>
using namespace std;

class User {

public:
    Inode* cdir;
    Inode* pdir;

    DirectoryEntry dent;
    char dbuf[DirectoryEntry::DIRSIZ];
    string curDirPath;

    string dirp;
    long arg[5];
    unsigned int	ar0[5];
    int u_error;

    OpenFiles ofiles;
    IOParameter IOParam;

    FileManager* fileManager;

    string ls;

public:
    User();
    ~User();

    void Ls();
    void Cd(string dirName);
    void Mkdir(string dirName);
    void Create(string fileName, string mode);
    void Delete(string fileName);
    void Open(string fileName, string mode);
    void Close(string fd);
    void Seek(string fd, string offset, string origin);
    void Write(string fd, string inFile, string size);
    void read(string fd, string outFile, string size);

private:
    bool IsError();
    void EchoError(int err);
    int INodeMode(string mode);
    int FileMode(string mode);
    bool checkPathName(string path);

};

#endif
