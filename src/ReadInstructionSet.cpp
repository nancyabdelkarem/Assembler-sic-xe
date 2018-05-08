#include "ReadInstructionSet.h"
#include<string>
#include <utility> //pairs
#include <tr1/unordered_map>
#include <ReadInstructionSet.h>
#include <vector>
#include <fstream>
#include<iostream>
#include <conio.h>

using namespace std;


void ReadInstructionSet::readInstructionSet()
{
    std::string word;
    vector<string> words;


    ifstream file ("sic_instructions.txt");

    if (!file)
    {
        cout << "There was a problem opening the file. Press any key to close.\n";
        getch();

    }

    //store words in array while outputting
    while( file )
    {
        file>>word;
        words.push_back(word);
    }
    for (int i=0; i<words.size()-1; i+=3)
    {
        key = words[i];
        format = words[i+1];
        opcode = words[i+2];
        pair <string, string> key_properties(format, opcode);
        instructionMap[key] = key_properties;
    }

}

std::tr1::unordered_map<string,pair<string,string> > ReadInstructionSet::getInstructionMap()
{
    return instructionMap;
}
