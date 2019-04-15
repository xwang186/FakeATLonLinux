#include<string>
#include<vector>
#ifndef IFACE_H
#define IFACE_H

#include "IUnknown.h"
using namespace std;
//IX is an interface returns a string result
interface ITextSearcher:IUnknown
{
        virtual std::string FindMatchedLines(string path, string regu)=0;
};

interface IFileManager:IUnknown
{
        virtual void Findfiles(string path, string regu,vector<string> &result)=0;
};

interface IZ:IUnknown
{
        virtual void Fz()=0;
};

extern "C"
{
        extern const IID IID_IX;
        extern const IID IID_IY;
        extern const IID IID_IZ;
}

#endif
