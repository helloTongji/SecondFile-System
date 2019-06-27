#ifndef BUFFER_H
#define BUFFER_H

#include "stdc++.h"
using namespace std;

class Buffer {

public:
    unsigned int flags;
    Buffer*	forw;
    Buffer*	back;
    int		wcount;
    unsigned char* addr;
    int		blkno;
    int		u_error;
    int		resid;
    int no;
public:
    Buffer();
    ~Buffer();
    void debugMark();
};

#endif
