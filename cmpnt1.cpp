#include <iostream>
#include "type.h"
#include "iface.h"
#include "guids.cpp"
#include<string>
#include<vector>
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
string FindLines(string filename, string regu);
void FindMatchedFiles(string path, string regu, vector<string> &result);
void trace1(const char* msg) { cout << "Component1:\t" << msg << endl; }

class TextSearch:public ITextSearcher
{
private:
        //IUnknown interface
        virtual HRESULT QueryInterface(const IID& iid, void** ppv);
        virtual ULONG   AddRef();
        virtual ULONG   Release();

        //IX interface
        virtual std::string FindMatchedLines(string path,string regu) {
                return FindLines( path, regu); }

public:
        //Constructor
        TextSearch():m_cRef(0){}

        //Destructor
        ~TextSearch(){ trace1("TextSearch component Destoryed by itself!"); }

private:
        long m_cRef;
};

HRESULT TextSearch::QueryInterface(const IID& iid, void** ppv)
{

        if(iid == IID_IX)
        {
                trace1("Return Pointer to ITextSearcher");
                *ppv = static_cast<ITextSearcher*>(this);
        }
        else if(iid == IID_IUnknown)
        {
                trace1("Return Pointer to IUnknown");
                *ppv = static_cast<IUnknown*>(this);
        }
        else
        {
                trace1("Interface is not surpport!");
                *ppv = NULL;
                return E_NOINTERFACE;
        }
        reinterpret_cast<IUnknown*>(*ppv)->AddRef();

        return S_OK;
}

ULONG TextSearch::AddRef()
{
        m_cRef++;
}

ULONG TextSearch::Release()
{
        if((--m_cRef) == 0)
        {
                delete this;
                return 0;
        }
        return m_cRef;
}

class FileMng:public IFileManager
{
private:
        //IUnknown interface
        virtual HRESULT QueryInterface(const IID& iid, void** ppv);
        virtual ULONG   AddRef();
        virtual ULONG   Release();

        //IY interface
        virtual void Findfiles(string path,string regu,vector<string> &result) {              
                FindMatchedFiles( path, regu, result);
                }

public:
        //Constructor
        FileMng():m_cRef(0){}

        //Destructor
        ~FileMng(){ trace1("FileManager component Destoryed by itself!"); }

private:
        long m_cRef;
};

HRESULT FileMng::QueryInterface(const IID& iid, void** ppv)
{

        if(iid == IID_IY)
        {
                trace1("Return Pointer to IFileManager");
                *ppv = static_cast<IFileManager*>(this);
        }
        else if(iid == IID_IUnknown)
        {
                trace1("Return Pointer to IUnknown");
                *ppv = static_cast<IUnknown*>(this);
        }
        else
        {
                trace1("Interface is not surpport!");
                *ppv = NULL;
                return E_NOINTERFACE;
        }
        reinterpret_cast<IUnknown*>(*ppv)->AddRef();

        return S_OK;
}

ULONG FileMng::AddRef()
{
        m_cRef++;
}

ULONG FileMng::Release()
{
        if((--m_cRef) == 0)
        {
                delete this;
                return 0;
        }
        return m_cRef;
}


extern "C" IUnknown* CreateInstance()
{
        IUnknown* pI = static_cast<ITextSearcher*>(new TextSearch);
        pI->AddRef();
        return pI;
}

extern "C" IUnknown* CreateFMInstance()
{
        IUnknown* pI = static_cast<IFileManager*>(new FileMng);
        pI->AddRef();
        return pI;
}
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <regex>
#include <dirent.h>
string FindLines(string filename, string regu) {
	regex reg(regu);
		ifstream infile(filename);
		int line = 1;
		if (!infile) {
			cerr << "Can not open file " << filename << ", maybe it is used by other applications!\n";
			return "[]";
		}
		ostringstream os;
		string currline;

		while (getline(infile, currline))
		{
			if (regex_match(currline, reg))
			{
				os << " line " << line<<" in file "<<filename<<endl;
			}
			line++;
		}
		
		return os.str();
}
void FindMatchedFiles(string path, string regu, vector<string> &result) {  
    struct dirent* ent = NULL;  
    DIR *pDir;  
    const char* realpath=path.c_str();
    regex reg(regu);
    pDir = opendir(realpath);  
    if (pDir == NULL) {  
        return;  
    }
    
    while (NULL != (ent = readdir(pDir))) {  
        if (ent->d_type == 8) {  
            //file  
            if (regex_match(ent->d_name, reg)){
                ostringstream pathbuilder;  
                pathbuilder<<path<<"/"<<ent->d_name;
		result.push_back(pathbuilder.str());
		}    
        } else {  
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {  
                continue;  
            }  
            //directory  
            std::string _path(path);  
            std::string _dirName(ent->d_name);  
            std::string fullDirPath = _path + "/" + _dirName;
            FindMatchedFiles(fullDirPath.c_str(), regu,result);  
        }  
    }  
}  