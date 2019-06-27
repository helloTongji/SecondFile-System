#include "Utility.h"
#include "File.h"
#include "User.h"
File::File() {
    flag = 0;
    count = 0;
    inode = NULL;
    offset = 0;
}

File::~File() {
}

OpenFiles::OpenFiles() {
    Utility::memset(processOpenFileTable, NULL, sizeof(processOpenFileTable));
}

OpenFiles::~OpenFiles() {
}
int OpenFiles::AllocFreeSlot() {
    User& u = g_User;
    for (int i = 0; i < OpenFiles::NFILE; i++) {
        if (this->processOpenFileTable[i] == NULL) {
            u.ar0[0] = i;
            return i;
        }
    }

    u.ar0[0] = -1;
    u.u_error = 24;
    return -1;
}
File* OpenFiles::GetF(int fd) {
    User& u = g_User;
    File* pFile;

    if (fd < 0 || fd >= OpenFiles::NFILE) {
        u.u_error = 9;
        return NULL;
    }

    pFile = this->processOpenFileTable[fd];
    if (pFile == NULL) {
        u.u_error = 9;
    }
    return pFile;
}
void OpenFiles::SetF(int fd, File* pFile) {
    if (fd < 0 || fd >= OpenFiles::NFILE) {
        return;
    }
    this->processOpenFileTable[fd] = pFile;
}
