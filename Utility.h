#ifndef UTILITY_H
#define UTILITY_H

#include"stdc++.h"
#include "DeviceDriver.h"
#include "User.h"
#include<QTextBrowser>
using namespace std;
extern User g_User;
extern DeviceDriver g_DeviceDriver;
extern BufferManager g_BufferManager;
extern SuperBlock g_SuperBlock;
extern InodeTable g_INodeTable;
extern FileSystem g_FileSystem;
extern FileManager g_FileManager;
extern OpenFileTable g_OpenFileTable;
extern QTextBrowser *g_Cmd;
extern int act_type;
class Utility{
public:
    static void memcpy(void *dest, const void *src, size_t n);
    static void memset(void *s, int ch, size_t n);
    static int memcmp(const void *buf1, const void *buf2, unsigned int count);
    static int min(int a, int b);
    static time_t time(time_t* t);
};
void cmdArgs(const string& cmd, vector<string>& args);
#endif
