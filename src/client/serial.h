#ifndef SERIAL_H
#define SERIAL_H

#include <windows.h>

HANDLE openSerial(const char* portName);
int    readSerial(HANDLE h, char* buf, int maxLen);
void   closeSerial(HANDLE h);

#endif
