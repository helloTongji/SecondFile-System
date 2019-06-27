#ifndef BUFFERMANAGER_H
#define BUFFERMANAGER_H

#include "Buffer.h"
#include "DeviceDriver.h"
#include "stdc++.h"
#include <unordered_map>
using namespace std;

class BufferManager {
public:
    static const int NBUF = 100;
    static const int BUFFER_SIZE = 512;
private:
    Buffer* bufferList;
    Buffer nBuffer[NBUF];
    unsigned char buffer[NBUF][BUFFER_SIZE];
    unordered_map<int, Buffer*> map;
    DeviceDriver* deviceDriver;

public:
    BufferManager();
    ~BufferManager();
    Buffer* GetBlk(int blkno);
    void Brelse(Buffer* bp);
    Buffer* Bread(int blkno);
    void Bwrite(Buffer* bp);
    void Bdwrite(Buffer* bp);
    void Bclear(Buffer* bp);
    void Bflush();
    void FormatBuffer();

private:
    void InitList();
    void DetachNode(Buffer* pb);
    void InsertTail(Buffer* pb);
    void debug();
};

#endif
