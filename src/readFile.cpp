#include "ReadFile.h"
#include <vector>
#include <string>
#include <Parsing.h>
#include <iostream>
#include <Validation.h>
#include <Addressing.h>
using namespace std;
Parsing parser;
Validation valid;
Addressing addressCalc;
int ReadFile::readInputFile(std::ifstream &InputFile)
{
    string line;
    vector<std::string> lines;
    if (InputFile)
    {
        for( std::string line; getline( InputFile, line ); )
        {
            lines.push_back(line);

        }
        InputFile.close();
    }

    for(int i =0; i<lines.size(); i++)
    {
        cout<< lines[i] << endl;
        convert(lines[i]);
        vector<string> h1 = parser.split(lines[i]);
        vector<string> parseRes = parser.parse(h1);
        addressCalc.addressCalculation(parseRes,i);
        vector<string> address = addressCalc.getAddresses();
        std::tr1::unordered_map<string,string> symbolTable =addressCalc.getSymbolTable();
std::tr1::unordered_map<std::string,std::string>::const_iterator got = symbolTable.find (parseRes.at(0));
        cout << "Label : " << parseRes.at(0) << endl;
        cout << "Mnemonic : " << parseRes.at(1)<<endl;
        cout << "Operand : " << parseRes.at(2)<< endl;
        cout << "Comment : " << parseRes.at(3)<< endl;
        cout<< "Address :" << address.at(i) << endl;
        if(got != symbolTable.end())
        {
            std:: string values = got->second;
            cout<<"value : "<<values<<endl;

}
        valid.checkValid(parseRes);
    }
    vector<string> error = valid.getErrors();
    for(int i =0; i<error.size(); i++)
    {
        cout<< "Error:" << error.at(i) << endl;
    }

    return 0;
}


void ReadFile::convert(string& s)
{
    for(int i=0; i<s.length(); i++)
    {
        s[i] = toupper(s[i]);
    }
}
