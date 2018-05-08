#ifndef READFILE_H
#define READFILE_H
#include <fstream>
#include <string>

using namespace std;

class ReadFile
{
public:
    int readInputFile(std::ifstream &InputFile);
    void convert(string& s);

};

#endif // READFILE_H
