#ifndef PARSING_H
#define PARSING_H
#include <vector>
#include <string>

using namespace std;

class Parsing
{
    vector<string> label;
    vector<string> menmonic;
    vector<string> operands;
    vector<string> comments;

public:
    vector<string> split(string s);
    vector<string> parse(vector<string> words);
    vector<string> getLabel();
    vector<string> getMenmonic();
    vector<string> getOperand();
    vector<string> getComments();

};

#endif // PARSING_H
