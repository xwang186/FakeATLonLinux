#pragma once
#include<string>
#include<vector>
using namespace std;
class Searcher
{
public:
	Searcher();
	~Searcher();
	string FindLines(string filename,string reg);
	void FindMatchedFiles(string path, string regu, vector<string>& result);
};