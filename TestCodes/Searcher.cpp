#include "Searcher.h"
#include<regex>

Searcher::Searcher()
{
}


Searcher::~Searcher()
{
}
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <dirent.h>
string Searcher::FindLines(string filename, string regu) {
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
void Searcher::FindMatchedFiles(string path, string regu, vector<string> &result) {  
    struct dirent* ent = NULL;  
    DIR *pDir;  
    const char* realpath=path.c_str();
    regex reg(regu);
    pDir = opendir(realpath);  
    if (pDir == NULL) {  
        return;  
    }
    ostringstream pathbuilder;  
    while (NULL != (ent = readdir(pDir))) {  
        if (ent->d_type == 8) {  
            //file  
            if (regex_match(ent->d_name, reg))
				{
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
            printf("%s/\n", ent->d_name);  
            FindMatchedFiles(fullDirPath.c_str(), regu,result);  
        }  
    }  
}  