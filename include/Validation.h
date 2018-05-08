#ifndef VALIDATION_H
#define VALIDATION_H
#include <vector>
#include <string>
#include <utility> //pairs
#include <tr1/unordered_map>

using namespace std;

class Validation
{
    //string address = "-";
    string programName;
    std::tr1::unordered_map<string,pair<string,string> > instructionMap;
    std::tr1::unordered_map<string,string> symbolTable;

    vector<string> errors;
public:
    void checkValid(vector<string> line);
    vector<string> getErrors();
};

#endif // VALIDATION_H
