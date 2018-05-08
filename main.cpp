#include <iostream>
#include <fstream>
#include <ReadInstructionSet.h>
#include <readFile.h>
using namespace std;

int main()
{
    ReadFile rd;
    // ReadInstructionSet ri;
    std::ifstream InputFile("test.txt");
    //ri.readInstructionSet();
    rd.readInputFile(InputFile);
    return 0;
}
