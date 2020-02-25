#include "parser.h"

parser::parser()
{
    initializeMap();
}

void parser::initializeMap()
{
    precedence['+'] = 2;
    precedence['-'] = 2;
    precedence['/'] = 3;
    precedence['*'] = 3;
    precedence['('] = 5;
}

string trimParanthesis(const string &userinput)
{
    u_int pos = 0;
    string ret(userinput);
    while((pos=ret.find_first_of("()")<ret.size()))
          ret.erase(pos,1);
    return ret;
}

bool parser::validExpression(const string &line)
{
    return balanced(line) && regex_match(trimParanthesis(line),valid);
}

bool parser::balanced(const string &line)
{

}
