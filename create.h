#ifndef CREATE_H
#define CREATE_H

#include <iostream>
#include "IUnknown.h"
#include <dlfcn.h>

using namespace std;

struct CREATE
{
        void* handle;
        void* handle1;
        IUnknown* CallCreateInstance(const char *name);
        IUnknown* CallCreateFMInstance(const char *name);
        void closeHandle();
};

#endif