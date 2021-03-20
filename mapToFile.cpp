#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>

using std::string;
using std::map;
using std::ofstream;
using std::ifstream;
using std::vector;

typedef map<string,string> stringMap;

bool mapToFile(const string &filename,const stringMap &fileMap)     //Write Map
{
    ofstream ofile;
    ofile.open(filename.c_str());
    if(!ofile)
    {
        return false;           //file does not exist and cannot be created.
    }
    for(stringMap::const_iterator iter= fileMap.begin(); iter!=fileMap.end(); ++iter)
    {
        ofile<<iter->first<<"|"<<iter->second;
        ofile<<"\n";
    }
    return true;
}
bool fileToMap(const std::string &filename, stringMap &fileMap)  //Read Map
{
    ifstream ifile;
    ifile.open(filename.c_str());
    if(!ifile)
        return false;   //could not read the file.
    string line;
    string key;
    vector<string> v_str;
    while(ifile>>line)
    {
        splitString(v_str,line,'|');
        for(vector<string>::iterator iter = v_str.begin();;++iter)        //First vector element is the key.
        {
            if(iter == v_str.begin())
            {
                fileMap[*iter]="Unavailable";
                key= *iter;
                continue;
            }
            fileMap[key]= *iter;
            break;
        }
    }
    return true;
}

int main()
{


  std::cin.get();
  return 0;
}
