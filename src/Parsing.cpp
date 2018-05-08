#include "Parsing.h"
#include <vector>
#include <string>
#include <iostream>
#include <Parsing.h>
using namespace std;

vector<string> Parsing::split(string s)
{
    vector<string> splitWords;
    int i = 0;
    std:: string comment = "";
    while(i < s.size())
    {
        while((i < s.size() && s.at(i) == ' ' )
                || (i < s.size() && s.at(i) == '\t') )
        {
            i++;
        }
        string word = "";
        while((i < s.size() && s.at(i) != ' ') && (i < s.size() && s.at(i) != '\t'))
        {
            if(s.at(i) == '.')
            {
                for(int j=i; j<s.size(); j++)
                {
                    comment.push_back(s.at(j));
                    i++;
                }
            }
            else if(s.at(i) == 'C' && s.at(i+1) == '\'' )
            {

                word.push_back(s.at(i));
                i++;
                word.push_back(s.at(i));
                i++;
                while(i < s.size() && s.at(i) != '\'')
                {

                    word.push_back(s.at(i));
                    i++;
                }
                if(i < s.size())
                {
                    word.push_back(s.at(i));
                }


            }
            else
            {
                word.push_back(s.at(i));
            }
            i++;
        }
        if(word != "")
        {
            splitWords.push_back(word);

        }
        i++;
    }
    if(comment != "")
    {
        comments.push_back(comment);
    }
    else
    {
        comments.push_back("-");
    }
    return splitWords;

}


vector<string> Parsing::parse(vector<string> words)
{
    if(words.size() == 0)
    {
        label.push_back("-");
        menmonic.push_back("-");
        operands.push_back("-");
    }
    else if(words.size() == 1)
    {
        label.push_back("-");
        menmonic.push_back(words.at(0));
        operands.push_back("-");
    }
    else if(words.size() == 2)
    {

        if(words.at(1) == "RSUB"||words.at(1) ==  "NOBASE" || words.at(1) == "END" || words.at(1) == "ORG" || words.at(1) == "START" )
        {
            label.push_back(words.at(0));
            menmonic.push_back(words.at(1));
            operands.push_back("-");
        }
        else
        {
            label.push_back("-");
            menmonic.push_back(words.at(0));
            operands.push_back(words.at(1));
        }
    }
    else if(words.size() == 3)
    {

        label.push_back(words.at(0));
        menmonic.push_back(words.at(1));
        operands.push_back(words.at(2));
        //  cout<<"HEEEEEEE" <<label.at(0) << endl;
    }
    else
    {
        cout<< " ERROR!" << endl;
    }
    vector<string> parseRes;
    parseRes.push_back(label.at(label.size() -1));
    parseRes.push_back(menmonic.at(menmonic.size() -1));
    parseRes.push_back(operands.at(operands.size() -1));
    parseRes.push_back(comments.at(comments.size() -1));
    return parseRes;
}

vector<string> Parsing::getComments()
{
    return comments;
}

vector<string> Parsing::getLabel()
{
    return label;
}

vector<string> Parsing::getMenmonic()
{
    return menmonic;
}

vector<string> Parsing::getOperand()
{
    return operands;
}

