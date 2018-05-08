#ifndef ADDRESSING_H
#define ADDRESSING_H
#include <vector>
#include <string>
#include <utility> //pairs
#include <tr1/unordered_map>

using namespace std;

class Addressing
{

    std::tr1::unordered_map<string,pair<string,string> > instructionMap;
    std::tr1::unordered_map<string,string> symbolTable;

    vector<string> addresses;
public:
    int DecimalAddressValue(string address);
    int addFormat(int currentAddress, int format);
    int hexCharToInt(char a);
    string DecimalToHexa(int addressInDecimal);
    void addressCalculation (vector<string> line,int index);
    string adjustAddress(string currentAddress);
    vector<string> getAddresses();
 std::tr1::unordered_map<string,string> getSymbolTable();

};

#endif // ADDRESSING_H
