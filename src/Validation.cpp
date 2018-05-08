#include "Validation.h"
#include <ReadInstructionSet.h>
#include <vector>
#include <string>
#include <ReadInstructionSet.h>
#include <utility> //pairs
#include <tr1/unordered_map>
#include <iterator>
#include <iostream>


using namespace std;

void Validation::checkValid(vector<string> line)
{
    string label = line.at(0);
    string menemonic = line.at(1);
    string operand = line.at(2);
    string comment = line.at(3);
    string registers = "AXLBST";

    if(label != "-")
    {
        std::tr1::unordered_map<std::string,pair<string,string> >::const_iterator got1 = instructionMap.find (label);
        if(got1 != instructionMap.end() || label =="END" || label =="START" )
        {
            errors.push_back("*error:label name is special name");
            return;
        }
    }
    else if(menemonic != "-")
    {
        string check = "";
        if(menemonic.at(0) == '+')
        {
            check = menemonic.substr(1, menemonic.size());

        }
        else
        {
            check = menemonic;
        }
        std::tr1::unordered_map<std::string,pair<string,string> >::const_iterator operationSearch = instructionMap.find (check);
        if((operationSearch == instructionMap.end()) &&  menemonic !="END" && menemonic !="START" && menemonic !="RESW"
                && menemonic !="RESB" && menemonic !="WORD" && menemonic !="BYTE"
          )
        {
            errors.push_back("*error:invalid directive");
            return;
        }


    }
//    // get the start address
//    if(line.at(1) == "START")
//    {
//        if(line.at(2) == "-")
//        {
//            address = "0000";
//        }
//        else
//        {
//            address = line.at(2);
//        }

    ReadInstructionSet instructions;
    instructions.readInstructionSet();
    instructionMap = instructions.getInstructionMap();
    //check if operand is too long
    if(label == "-" && operand == "-" && menemonic == "-")
    {
        errors.push_back("-");
    }

    else if(menemonic == "START")
    {
        if(label == "-")
        {
            errors.push_back("*error: Missing program name");

        }
        else
        {
            programName = label;
            errors.push_back("-");
        }
    }
    else if(menemonic == "END")
    {
        if(operand != programName && operand != "-")
        {
            errors.push_back("*error: End should be followed by program name");

        }
        else
        {
            errors.push_back("-");
        }

    }
    else if(operand.size()>18)
    {
        errors.push_back("*error:operand is too long");
    }
    //check for label size
    else if(label.size()> 8)
    {
        errors.push_back("*error:label is too long");
    }
    //check if label start with number
    else if((label.at(0)<'A' || label.at(0)>'Z') && label != "-")
    {
        errors.push_back("*error:label must start with a letter");
    }
    //check if label already exists

//    else if(got != symbolTable.end())
//    {
//
//        errors.push_back("*error:label already exist");
//    }
    // check if label is special name

    else if(menemonic=="ADDR"|| menemonic =="SUBR"|| menemonic=="MULR"|| menemonic =="DIVR"|| menemonic=="RMO"||menemonic == "COMPR")
    {
        //check if one operand added
        if(operand == "-")
        {
            errors.push_back("*error:should have an operand");
        }
        else if(operand.find(",") == std::string::npos)
        {
            errors.push_back("*error:should have 2 registers");
        }
        else
        {
            string first = operand.substr(0, operand.find(","));
            string second = operand.substr(operand.find(",") + 1, operand.size() - 1);
            //cout <<"HERE " <<first << registers.find(first) << " " << second <<  registers.find(second) <<endl;
            //check if register exists
            if(registers.find(first) == std::string::npos || registers.find(second) == std::string::npos )
            {

                errors.push_back("*error:Invalid registers");
            }
            else
            {
                errors.push_back("-");
            }
        }
    }
    else if(menemonic == "TIXR")
    {
        //check if has more than one register
        if(operand == "-")
        {
            errors.push_back("*error:should have an operand");
        }
        else if(operand.find(",") != std::string::npos)
        {
            errors.push_back("*error:should have one register");
        }
        else if(registers.find(operand) == std::string::npos)
        {
            errors.push_back("*error:Invalid registers");
        }
        else
        {

            errors.push_back("-");

        }
    }
    else if(menemonic =="J"||menemonic =="JSUB"|| menemonic =="JEQ"|| menemonic =="JLT"||
            menemonic =="JGT"|| menemonic =="TD"|| menemonic=="RD"||menemonic=="WD")
    {
        if(operand.find(",") != std::string::npos)
        {
            errors.push_back("*error:No indexing is allowed");
        }
        else if(operand == "-")
        {
            errors.push_back("*error:should have an operand");
        }
        else
        {
            errors.push_back("-");
        }
    }
    else if(menemonic == "RSUB")
    {
        if(operand != "-")
        {
            errors.push_back("*error:No operand is allowed");
        }
        else
        {
            errors.push_back("-");
        }
    }
    else if(menemonic == "RESW" || menemonic == "RESB"||menemonic == "BYTE" ||menemonic == "WORD")
    {
        errors.push_back("-");

    }
    else
    {
        // second case pass2
        //one operand
        if(operand == "-")
        {
            errors.push_back("*error:should have an operand");
        }
        else if(operand.find(",") != std::string::npos)
        {
            //check operand exists
            string reg = operand.substr(operand.find(",") + 1, operand.size() - 1);
            if(reg != "X")
            {

                errors.push_back("*error:Invalid register");
            }
        }
        else
        {
            errors.push_back("-");
        }
    }

}


vector<string> Validation::getErrors()
{
    return errors;
}


