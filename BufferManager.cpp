#include "BufferManager.h"
#include "Utility.h"
#include<QDebug>
BufferManager::BufferManager() {
    bufferList = new Buffer;
    InitList();
    deviceDriver = &g_DeviceDriver;
}

BufferManager::~BufferManager() {
    Bflush();
    delete bufferList;
}

void BufferManager::FormatBuffer() {
    Buffer emptyBuffer;
    for (int i = 0; i < NBUF; ++i) {
        Utility::memcpy(nBuffer + i, &emptyBuffer, sizeof(Buffer));
    }
    InitList();
}

void BufferManager::InitList() {
    for (int i = 0; i < NBUF; ++i) {
        if (i) {
            nBuffer[i].forw = nBuffer + i - 1;
        }
        else {
            nBuffer[i].forw = bufferList;
            bufferList->back = nBuffer + i;
        }

        if (i + 1 < NBUF) {
            nBuffer[i].back = nBuffer + i + 1;
        }
        else {
            nBuffer[i].back = bufferList;
            bufferList->forw = nBuffer + i;
        }
        nBuffer[i].addr = buffer[i];
        nBuffer[i].no = i;
    }
}
void BufferManager::DetachNode(Buffer* pb) {
    if (pb->back == NULL) {
        return;
    }
    pb->forw->back = pb->back;
    pb->back->forw = pb->forw;
    pb->back = NULL;
    pb->forw = NULL;
}

void BufferManager::InsertTail(Buffer* pb) {
    if (pb->back != NULL) {
        return;
    }
    pb->forw = bufferList->forw;
    pb->back = bufferList;
    bufferList->forw->back = pb;
    bufferList->forw = pb;
}

Buffer* BufferManager::GetBlk(int blkno) {
    Buffer* pb;
    if (map.find(blkno) != map.end()) {
        pb = map[blkno];
        DetachNode(pb);
        return pb;
    }
    pb = bufferList->back;
    if (pb == bufferList) {
        QString inputStr="无Buffer可供使用\n";
        g_Cmd->append(inputStr);
        return NULL;
    }
    DetachNode(pb);
    map.erase(pb->blkno);
    if (pb->flags&128) {
        deviceDriver->write(pb->addr, BUFFER_SIZE, pb->blkno*BUFFER_SIZE);
    }
    pb->flags &= ~(128 | 4);
    pb->blkno = blkno;
    map[blkno] = pb;
    return pb;
}
void BufferManager:: Brelse(Buffer* pb) {
    InsertTail(pb);
}
Buffer* BufferManager::Bread(int blkno) {
    Buffer* pb = GetBlk(blkno);
    if (pb->flags&(4 | 128)) {
        return pb;
    }
    deviceDriver->read(pb->addr, BUFFER_SIZE, pb->blkno*BUFFER_SIZE);
    pb->flags |= 4;
    return pb;
}
void BufferManager::Bwrite(Buffer *pb) {
    pb->flags &= ~(128);
    deviceDriver->write(pb->addr, BUFFER_SIZE, pb->blkno*BUFFER_SIZE);
    pb->flags |= (4);
    this->Brelse(pb);
}
void BufferManager::Bdwrite(Buffer* bp) {
    bp->flags |= (128 | 4);
    this->Brelse(bp);
    return;
}
void BufferManager::Bclear(Buffer *bp) {
    Utility::memset(bp->addr, 0, BufferManager::BUFFER_SIZE);
    return;
}
void BufferManager::Bflush() {
    Buffer* pb = NULL;
    for (int i = 0; i < NBUF; ++i) {
        pb = nBuffer + i;
        if ((pb->flags & 128)) {
            pb->flags &= ~(128);
            deviceDriver->write(pb->addr, BUFFER_SIZE, pb->blkno*BUFFER_SIZE);
            pb->flags |= (4);
        }
    }
}

void BufferManager::debug() {
    for (Buffer* pb = bufferList->back; pb != bufferList; pb = pb->back) {
        pb->debugMark();
    }
    QString inputStr="\n";
    g_Cmd->append(inputStr);
}
