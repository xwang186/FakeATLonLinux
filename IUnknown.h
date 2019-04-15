#ifndef IUNKNOWN_H
#define IUNKNOWN_H

#include "type.h"

interface IUnknown
{
        virtual HRESULT  QueryInterface(const IID& iid, void** ppv)=0;
        virtual ULONG    AddRef()=0;
        virtual ULONG    Release()=0;
};

#endif
