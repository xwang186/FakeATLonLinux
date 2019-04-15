#include "create.h"

typedef IUnknown* (*CREATEFUNCPTR)();

IUnknown* CREATE::CallCreateInstance(const char* name)
{
        CREATEFUNCPTR   CreateInstance;
        char*           error;
        IUnknown*       pUnknown;

        handle = dlopen(name , RTLD_LAZY);

        if(!handle)
        {
                cout << "Load lib " << name << " fail!" << endl;
                exit(1);
        }

        dlerror();
        *(void**)(&CreateInstance) = dlsym(handle, "CreateInstance");
        if ((error = dlerror()) != NULL)
        {
                cout << error << endl;
                exit(1);
        }

        pUnknown = CreateInstance();

//      dlclose(handle);
        return pUnknown;
}

IUnknown* CREATE::CallCreateFMInstance(const char* name)
{
        CREATEFUNCPTR   CreateFMInstance;
        char*           error;
        IUnknown*       pUnknown;

        handle1 = dlopen(name , RTLD_LAZY);

        if(!handle1)
        {
                cout << "Load lib " << name << " fail!" << endl;
                exit(1);
        }

        dlerror();
        *(void**)(&CreateFMInstance) = dlsym(handle1, "CreateFMInstance");
        if ((error = dlerror()) != NULL)
        {
                cout << error << endl;
                exit(1);
        }

        pUnknown = CreateFMInstance();

//      dlclose(handle);
        return pUnknown;
}
void   CREATE::closeHandle()
{
        dlclose(handle);
}

bool operator==(const IID& guid1, const IID& guid2)
{
        if(guid1.Data1 != guid2.Data1)
                return false;
        if(guid1.Data2 != guid2.Data2)
                return false;
        if(guid1.Data3 != guid2.Data3)
                return false;

        for(int i = 0; i < 8; i++)
        {
                if(guid1.Data4[i] != guid2.Data4[i])
                        return false;
        }

        return true;
}