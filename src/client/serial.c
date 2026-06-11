#include "serial.h"
#include <stdio.h>

HANDLE openSerial(const char* portName) {

    HANDLE h = CreateFileA(
        portName,
        GENERIC_READ,
        0, NULL,
        OPEN_EXISTING,
        0, NULL
    );

    if (h == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Controller no encontrado en %s\n", portName);
        return INVALID_HANDLE_VALUE;
    }

    DCB dcb = {0};
    dcb.DCBlength = sizeof(DCB);
    GetCommState(h, &dcb);
    dcb.BaudRate = CBR_115200;
    dcb.ByteSize = 8;
    dcb.Parity   = NOPARITY;
    dcb.StopBits = ONESTOPBIT;
    SetCommState(h, &dcb);

    /* ReadFile retorna inmediatamente con lo que haya disponible */
    COMMTIMEOUTS timeouts        = {0};
    timeouts.ReadIntervalTimeout = MAXDWORD;
    SetCommTimeouts(h, &timeouts);

    return h;
}

int readSerial(HANDLE h, char* buf, int maxLen) {
    if (h == INVALID_HANDLE_VALUE) return 0;
    DWORD bytesRead = 0;
    ReadFile(h, buf, (DWORD)maxLen, &bytesRead, NULL);
    return (int)bytesRead;
}

void closeSerial(HANDLE h) {
    if (h != INVALID_HANDLE_VALUE) CloseHandle(h);
}
