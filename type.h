#ifndef TYPE_H
#define TYPE_H

typedef long            HRESULT;
typedef unsigned long   ULONG;

typedef struct _GUID
{
    unsigned long Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char Data4[8];
} GUID;
typedef GUID IID;

#define interface struct

#define E_NOINTERFACE 0x80004002L
#define S_OK  0

#endif