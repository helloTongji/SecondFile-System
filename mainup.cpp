#include "Inode.h"
#include "File.h"
#include "FileSystem.h"
#include "OpenFileManager.h"
#include "FileManager.h"
#include "User.h"
#include"Utility.h"
#include <iostream>
#include <unordered_map>
#include<QDebug>
using namespace std;

DeviceDriver g_DeviceDriver;
BufferManager g_BufferManager;
OpenFileTable g_OpenFileTable;
SuperBlock g_SuperBlock;
FileSystem g_FileSystem;
InodeTable g_INodeTable;
FileManager g_FileManager;
User g_User;

void cmdArgs(const string& cmd, vector<string>& args) {
    args.clear();
    string str;
    unsigned int p, q;
    for (p = 0, q = 0; q < cmd.length(); p = q + 1) {
        q = cmd.find_first_of(" \n", p);
        str = cmd.substr(p, q - p);
        if (!str.empty()) {
            args.push_back(str);
        }
        if (q == string::npos)
            return;
    }
}
