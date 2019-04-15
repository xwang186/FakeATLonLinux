#include <iostream>
#include "iface.h"
#include "create.h"
#include "guids.cpp"
#include <string>
void trace(const char* msg) { cout << "Client1:\t" << msg << endl; }

int main(int argc, char** argv)
{
        HRESULT hr;
        
        CREATE  create;


        cout << "Demostrating my project..."<<endl;
        cout << "Load libcmpnt1.so as the target linked file:"<<endl;

        string linkfile = "libcmpnt1.so";
        const char *name=linkfile.c_str();
        
        cout << "Testing the FileMng Object, from interface IFileManager"<<endl;

        trace("Get an IUnknown pointer.");
        IUnknown* pUnknown1 = create.CallCreateFMInstance(name);
        if(pUnknown1 == NULL)
        {
                trace("CallCreateInstance fail!");
                exit(1);
        }

        trace("Get Interface IFileManager.");
        //string reg = "(.*)(cpp$)";
        //string folderpath=".";
        //string linereg = "(v)(.*)";
        //full test: ./client1 "(.*)(cpp$)" "." "(v)(.*)"
        string reg =argv[1];  
        string folderpath=argv[2];
        string linereg = argv[3];
        cout<<"Finding regular expresion "<<reg<<" under path "<<folderpath<<"..."<<endl;
        IFileManager* pIF = NULL;

        hr = pUnknown1->QueryInterface(IID_IY, (void**)&pIF);
        vector<string> result;
        if(hr >= 0)
        {
                trace("Success get the IFileManager.");

                pIF->Findfiles(folderpath,reg,result);
                cout<<result.size()<<" files are found."<<endl;
                int counter=0;
                for (string i:result)
                {
                     cout<<"File "<<counter<<": "<<i<<endl;
                     counter++;
                }
                pIF->Release();
        }
        else
        {
                trace("Counld not get the IFileManager interface.");
        }
        pUnknown1->Release();
        cout << "\nTesting the TextSearch Object, from interface IFileManager"<<endl;
        IUnknown* pUnknown = create.CallCreateInstance(name);
        trace("Get Interface ITextSearcher.");

        ITextSearcher* pIX = NULL;
        
        hr = pUnknown->QueryInterface(IID_IX, (void**)&pIX);
        cout<<"Finding regular expresion "<<linereg<<" for all files of test 1 result..."<<endl;
        if(hr >= 0)
        {
                trace("Success get the ITextSearcher.");
                for(string filep:result){
                std::string lines=pIX->FindMatchedLines(filep,linereg);
                cout<<lines<<endl;               
                }
                pIX->Release();
        }
        else
        {
                trace("Counld not get the IX interface.");
        }
        trace("Release the IUnknown interface.");
        pUnknown->Release();

        create.closeHandle();
        return 0;
}