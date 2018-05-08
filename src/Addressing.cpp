#include "Addressing.h"
#include <ReadInstructionSet.h>
#include <vector>
#include <string>
#include <utility> //pairs
#include <tr1/unordered_map>
#include <iterator>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <conio.h>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <algorithm>
using namespace std;



int Addressing::DecimalAddressValue(string address)
{
    double decimalValue = 0;
    int position = 0;
    for(int i= (int)address.length()-1; i>=0; i--)
    {
        decimalValue += hexCharToInt(address.at(i))*pow(16.0,position);
        position++;
    }
    return (int)decimalValue;
}
int Addressing::addFormat(int currentAddress, int format)
{
    currentAddress += format;
    return currentAddress;
}
int Addressing::hexCharToInt(char a)
{
    if(a>='0' && a<='9')
        return(a-48);
    else if(a>='A' && a<='Z')
        return(a-55);
    else
        return(a-87);
}
string Addressing::DecimalToHexa(int addressInDecimal)
{
    long int quotient;
    int i=1,j,temp;
    char hexadecimalNumber[100];



    quotient =addressInDecimal;

    while(quotient!=0)
    {
        temp = quotient % 16;

        //To convert integer into character
        if( temp < 10)
            temp =temp + 48;
        else
            temp = temp + 55;

        hexadecimalNumber[i++]= temp;
        quotient = quotient / 16;
    }
    std::stringstream hexaStringRepresentation;
    for(j = i -1 ; j> 0; j--)
        hexaStringRepresentation <<hexadecimalNumber[j];
    return hexaStringRepresentation.str();
}

string currentAddress ;
string addressValue;
string notFound;

void Addressing::addressCalculation (vector<string> line,int index)
{
    ReadInstructionSet instructions;
    instructions.readInstructionSet();
    instructionMap = instructions.getInstructionMap();
    string label = line.at(0);
    string mnemonic = line.at(1);
    string operand = line.at(2);
    string comment = line.at(3);
    int format=0;

    if(mnemonic =="START")
    {
        string startAddress = operand;
        //default start address if no operand at START
        if(startAddress=="-")
        {
            startAddress="0000";
        }
        //if there is operand at START make it the address of the first instruction
        startAddress= adjustAddress(startAddress);

        addresses.push_back(startAddress);
        currentAddress=startAddress;




    }
    else if(mnemonic !="END")
    {
        bool dash=false;

        if((mnemonic == "-" && operand=="-"&&label=="-"))
        {
            dash=true;
            //leave address field blank
            addresses.push_back(" ");
        }
        //if the line is not comment but have no operation
        if(mnemonic=="-"&&(operand !="-"||label !="-"))
        {
            dash=true;
            //invalid instruction
            //can't have address if there was no operation
            addresses.push_back(" ");
        }
        if(mnemonic=="BASE"||mnemonic=="NOBASE"||mnemonic=="LTORG")
        {
            dash=true;
            //has no address
            addresses.push_back(" ");
        }
        if(!dash && notFound!="not found")
        {
            addresses.push_back(currentAddress);
        }
        if(label != "-")
        {
            std::tr1::unordered_map<std::string,std::string>::const_iterator got = symbolTable.find (label);
            if(got == symbolTable.end())
            {
                symbolTable[label]=addressValue;
            }


        }
        //calculate address for next line based on current line
        notFound=" ";
        bool found =false;
        //check if format four
        char firstchar = mnemonic.at(0);
        if(firstchar == '+')
        {
            //the instruction is format 4
            mnemonic.erase(0,1);
            //look for instruction in instructionMap
            std::tr1::unordered_map<std::string,pair<string,string>>::const_iterator got = instructionMap.find (mnemonic);

            if ( got != instructionMap.end() )
            {
                found = true;
                format = 4;
                currentAddress = DecimalToHexa(addFormat(DecimalAddressValue(currentAddress),format));
            }
        }//end if format 4
        else
        {
            //format 2 or 3 find out from instructionMap
            std::tr1::unordered_map<std::string,pair<string,string>>::const_iterator got = instructionMap.find (mnemonic);
            if ( got != instructionMap.end() )
            {
                found = true;
                //get properties of the operation
                pair <string, string> key_properties = got->second;
                string formatOfOp = key_properties.first ;

                if(formatOfOp == "2")
                {
                    format =2;
                }
                else if(formatOfOp == "3/4")
                {
                    format = 3;
                }
                currentAddress = DecimalToHexa(addFormat(DecimalAddressValue(currentAddress),format));



            }

        }//end of operations in the instructionMap
        if(mnemonic == "WORD")
        {
            found=true;
            // add 3 to address
            format = 3;
            currentAddress = DecimalToHexa(addFormat(DecimalAddressValue(currentAddress),format));
        }
        else if(mnemonic == "RESW")
        {
            found=true;
            string numOfWords = operand;
            int numOfWord;
            istringstream ( numOfWords ) >> numOfWord;
            // 3 * numofword to address
            format = 3* numOfWord;
            currentAddress = DecimalToHexa(addFormat(DecimalAddressValue(currentAddress),format));


        }
        else if(mnemonic == "RESB")
        {
            found=true;
            string numOfBytes = operand;
// 1* numofbyte to address
            int numOfbyte;
            istringstream ( numOfBytes ) >> numOfbyte;
            format = 1* numOfbyte;
            currentAddress = DecimalToHexa(addFormat(DecimalAddressValue(currentAddress),format));
        }
        else if(mnemonic== "BYTE")
        {
            found=true;
            string byteValue = operand;
            if(byteValue.at(0) == 'X' )
            {
                //add 1 to address
                format = 1;
                currentAddress = DecimalToHexa(addFormat(DecimalAddressValue(currentAddress),format));

            }
            else if(byteValue.at(0) == 'C')
            {

                int k = 2;
                int length = 0;
                while(k<byteValue.size()-1)
                {
                    length++;
                    k++;
                }
// add lenght to the address
                format = length;
                currentAddress = DecimalToHexa(addFormat(DecimalAddressValue(currentAddress),format));

            }

        }
        if(found )
        {
            addressValue=currentAddress;
            currentAddress=adjustAddress(currentAddress);

        }
        else if (!found && !dash)
        {
            notFound="not found";
            addresses.push_back(" ");
        }



    }
//found end
    else
    {
        addresses.push_back(" ");

    }
}
string Addressing::adjustAddress(string currentAddress)
{
    if(currentAddress.size()<4)
    {
        if(currentAddress.size()== 3)
        {
            currentAddress = "0"+currentAddress;
        }
        else if (currentAddress.size()==2)
        {
            currentAddress = "00"+currentAddress;
        }
        else
        {
            currentAddress ="000"+currentAddress;
        }
    }
    return currentAddress;
}

vector<string> Addressing:: getAddresses()
{

    return addresses;
}
std::tr1::unordered_map<string,string> Addressing::getSymbolTable()
{
    return symbolTable;
}


