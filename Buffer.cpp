#include "Buffer.h"
#include "BufferManager.h"
#include <iostream>
#include <iomanip>
#include <ctype.h>
#include<QDebug>
#include<qdebug.h>
#include"Utility.h"
using namespace std;
Buffer::Buffer() {
    flags = 0;
    forw = NULL;
    back = NULL;
    wcount = 0;
    addr = NULL;
    blkno = -1;
    u_error = -1;
    resid = 0;

    no=0;
}

Buffer::~Buffer() {

}

void Buffer::debugMark() {
    QString inputStr="no = ";
    inputStr=inputStr+QString::number(no)+" blkno = "+QString::number(blkno)+" flag = "+(flags&4 ? " DONE " : " ")+(flags&128 ? " DELWRI " : " ")+"\n";
    g_Cmd->append(inputStr);
}
