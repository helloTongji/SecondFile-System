#include "User.h"
#include "Utility.h"
#include <iostream>
#include <fstream>
#include<QDebug>
#include<qdebug.h>
#include<QFile>
using namespace std;
User::User() {
    u_error = 0;
    fileManager = &g_FileManager;
    dirp = "/";
    curDirPath = "/";
    cdir = fileManager->rootDirINode;
    pdir = NULL;
    Utility::memset(arg, 0, sizeof(arg));
}

User::~User() {
}


void User::Mkdir(string dirName) {
    if (!checkPathName(dirName)) {
        return;
    }
    arg[1] = Inode::IFDIR;
    fileManager->Creat();
    IsError();
}

void User::Ls() {
    ls.clear();
    fileManager->Ls();
    if (IsError()) {
        return;
    }
    g_Cmd->append(QString::fromStdString(ls));
}

void User::Cd(string dirName) {
    if (!checkPathName(dirName)) {
        return;
    }
    fileManager->ChDir();
    IsError();
}

void User::Create(string fileName, string mode) {
    if (!checkPathName(fileName)) {
        return;
    }
    int md = INodeMode(mode);
    if (md == 0) {
        g_Cmd->append("该创建方式未被定义!  \n");
        return;
    }

    arg[1] = md;
    fileManager->Creat();
    IsError();
}

void User::Delete(string fileName) {
    if (!checkPathName(fileName)) {
        return;
    }
    fileManager->UnLink();
    IsError();
}

void User::Open(string fileName, string mode) {
    if (!checkPathName(fileName)) {
        return;
    }
    int md = FileMode(mode);
    if (md == 0) {
        g_Cmd->append("该文件打开方式未被定义 !  \n");
        return;
    }

    arg[1] = md;
    fileManager->Open();
    if (IsError())
        return;
    QString inputStr="打开文件成功 文件句柄fd=";
    inputStr=inputStr+QString::number(ar0[0])+"\n";
    g_Cmd->append(inputStr);
}

void User::Close(string sfd) {
    if (sfd.empty() || !isdigit(sfd.front())) {
        g_Cmd->append("参数 fd 不能为空或是非数字 ! \n");
        return;
    }
    arg[0] = stoi(sfd);;
    fileManager->Close();
    IsError();
}

void User::Seek(string sfd, string offset, string origin) {
    if (sfd.empty() || !isdigit(sfd.front())) {
        g_Cmd->append("参数 fd 不能为空或是非数字 ! \n");
        return;
    }
    if (offset.empty()) {
        g_Cmd->append("参数 offset 不能为空 !\n");
        return;
    }
    if (origin.empty() || !isdigit(origin.front())) {
        g_Cmd->append("参数 origin 不能为空或是非数字! \n");
        return;
    }
    arg[0] = stoi(sfd);
    arg[1] = stoi(offset);
    arg[2] = stoi(origin);
    fileManager->Seek();
    IsError();
}

void User::Write(string sfd, string inFile, string size) {
    if (sfd.empty() || !isdigit(sfd.front())) {
        g_Cmd->append("参数（文件句柄）不能为空或是非数字 ! \n");
        return;
    }
    int fd = stoi(sfd);

    int usize;
    if (size.empty() || (usize = stoi(size)) < 0) {
        g_Cmd->append("参数个数应大于等于0! \n");
        return;
    }

    char *buffer = new char[usize];
    qDebug()<<QString::fromStdString(inFile);
    fstream fin(inFile, ios::out | ios::app);//已修改过


    QFile file(QString::fromStdString(inFile));
    file.open(QIODevice::ReadOnly);
    file.read(buffer,usize);
    if (!fin) {
        QString inputStr="文件 " ;
        inputStr=inputStr+QString::fromStdString(inFile)+" 打开失败! \n";
        g_Cmd->append(inputStr);
        return;
    }
    fin.close();
    arg[0] = fd;
    arg[1] = (long)buffer;
    arg[2] = usize;
    qDebug()<<QString::fromStdString(inFile);
    fileManager->Write();

    if (IsError())
        return;
    QString inputStr="fwrite操作写入" ;
    inputStr=inputStr+QString::number(ar0[0])+"字节成功 !\n";
    g_Cmd->append(inputStr);


    delete[]buffer;
}

void User::read(string sfd, string outFile, string size) {
    if (sfd.empty() || !isdigit(sfd.front())) {
        g_Cmd->append("参数（文件句柄）不能为空或是非数字 ! \n");
        return;
    }
    int fd = stoi(sfd);

    int usize;
    if (size.empty() || !isdigit(size.front()) || (usize = stoi(size)) < 0) {
        g_Cmd->append("参数个数不对");
        return;
    }
    char *buffer = new char[usize];
    arg[0] = fd;
    arg[1] = (long)buffer;
    arg[2] = usize;
    fileManager->read();
    if (IsError())
        return;
    QString inputSTr="fread操作读取 " ;
    inputSTr=inputSTr+QString::number(ar0[0])+"字节成功: ";
    g_Cmd->append(inputSTr);

    QString loopStr="";
    if (outFile.empty()) {
        for (unsigned int i = 0; i < ar0[0]; ++i) {
            loopStr=loopStr+(char)buffer[i];
        }
        g_Cmd->append(QString(QLatin1String(buffer)));
        return;
    }
    fstream fout(outFile, ios::out | ios::binary);
    if (!fout) {
        QString inputStr="文件 ";
        inputStr=inputStr+QString::fromStdString(outFile)+ " 打开失败! \n";
        g_Cmd->append(inputStr);
        return;
    }
    fout.write(buffer, ar0[0]);
    fout.close();
    QString inputStr="fread操作读出到 ";
    inputStr=inputStr+QString::fromStdString(outFile)+ " 文件完成 ! \n";
    g_Cmd->append(inputStr);
    delete[]buffer;
}

int User::INodeMode(string mode) {
    int md = 0;
    if (mode.find("-r") != string::npos) {
        md |= Inode::IREAD;
    }
    if (mode.find("-w") != string::npos) {
        md |= Inode::IWRITE;
    }
    if (mode.find("-rw") != string::npos) {
        md |= (Inode::IREAD | Inode::IWRITE);
    }
    return md;
}

int User::FileMode(string mode) {
    int md = 0;
    if (mode.find("-r") != string::npos) {
        md |= File::FREAD;
    }
    if (mode.find("-w") != string::npos) {
        md |= File::FWRITE;
    }
    if (mode.find("-rw") != string::npos) {
        md |= (File::FREAD | File::FWRITE);
    }
    return md;
}

bool User::checkPathName(string path) {
    if (path.empty()) {
        g_Cmd->append("参数（文件路径）不能为空 ! \n");
        return false;
    }

    if (path.substr(0, 2) != "..") {
        dirp = path;
    }
    else {
        string pre = curDirPath;
        unsigned int p = 0;
        for (; pre.length() > 3 && p < path.length() && path.substr(p, 2) == ".."; ) {
            pre.pop_back();
            pre.erase(pre.find_last_of('/') + 1);
            p += 2;
            p += p < path.length() && path[p] == '/';
        }
        dirp = pre + path.substr(p);
    }

    if (dirp.length() > 1 && dirp.back() == '/') {
        dirp.pop_back();
    }

    for (unsigned int p = 0, q = 0; p < dirp.length(); p = q + 1) {
        q = dirp.find('/', p);
        q = min(q, (unsigned int)dirp.length());
        if (q - p > DirectoryEntry::DIRSIZ) {
            g_Cmd->append("文件名或路径名不应超过28个字符 ! \n");
            return false;
        }
    }
    return true;
}

bool User::IsError() {
    if (u_error != 0) {
        QString inputStr="errno = ";
        inputStr=inputStr+QString::number(u_error);
        g_Cmd->append(inputStr);

        EchoError(u_error);
        u_error = 0;
        return true;
    }
    return false;
}

void User::EchoError(int err) {
    string estr;
    switch (err) {
    case 0:
        estr = " No u_error ";
        break;
    case 2:
        estr = " 没有这样的文件或目录 ";
        break;
    case 9:
        estr = " 文件数出错 ";
        break;
    case 13:
        estr = " 访问拒绝 ";
        break;
    case 20:
        estr = " 不是一个目录 ";
        break;
    case 23:
        estr = " 文件表溢出，无可用File节点 ";
        break;
    case 24:
        estr = " 当前打开文件数量过多";
        break;
    case 27:
        estr = " 文件过大";
        break;
    case 28:
        estr = " 设备无空闲位置 ";
        break;
    default:
        break;
    }
    g_Cmd->append(QString::fromStdString(estr));
}
