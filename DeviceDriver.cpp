#define _CRT_SECURE_NO_WARNINGS
#include "DeviceDriver.h"
#include<QString>
#include"Utility.h"
const char * DeviceDriver::DISK_FILE_NAME = "MyDisk.img";

DeviceDriver::DeviceDriver() {
    fp = fopen(DISK_FILE_NAME, "rb+");
}

DeviceDriver::~DeviceDriver() {
    if (fp) {
        fclose(fp);
    }
}
bool DeviceDriver::Exists() {
    return fp != NULL;
}
void DeviceDriver::Construct() {
    fp = fopen(DISK_FILE_NAME, "wb+");
    if (fp == NULL) {
        QString inputStr="打开或新建文件"+QString("%1").arg(DISK_FILE_NAME)+"失败！";
        g_Cmd->append(inputStr);
        exit(-1);
    }
}
void DeviceDriver::write(const void* buffer, unsigned int size, int offset, unsigned int origin) {
    if (offset >= 0) {
        fseek(fp, offset, origin);
    }
    fwrite(buffer, size, 1, fp);
}
void DeviceDriver::read(void* buffer, unsigned int size, int offset, unsigned int origin) {
    if (offset >= 0) {
        fseek(fp, offset, origin);
    }
    fread(buffer, size, 1, fp);
}
