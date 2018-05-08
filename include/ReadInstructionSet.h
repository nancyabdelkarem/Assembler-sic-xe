#ifndef READINSTRUCTIONSET_H
#define READINSTRUCTIONSET_H
#include<string>
#include <utility> //pairs
#include <tr1/unordered_map>

using namespace std;

class ReadInstructionSet
{
    std::tr1::unordered_map<string,pair<string,string> > instructionMap;
    string key;
    string format;
    string opcode;
public:
    void readInstructionSet();
    std::tr1::unordered_map<string,pair<string,string> > getInstructionMap();


};

#endif // READINSTRUCTIONSET_H
