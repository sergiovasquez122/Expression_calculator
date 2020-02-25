#ifndef PARSER_H
#define PARSER_H
#include <map>
#include <stack>
#include <queue>
#include <regex>
#include "polynomial.h"
using std::stack;
using std::queue;
using std::map;
using std::regex;
class parser
{
public:
    parser();
    void storeExpression(const string& line);
    void operator()(const string& line);
private:
    void initializeMap();
    bool balanced(const string& line);
    bool validExpression(const string& line);
    void infixToPostfix(const string& line);
    map<char,int> precedence;
    stack<char> operandStack;
    stack<char> operatorStack;
    queue<char> postfix;
    regex valid;
};

string trimParanthesis(const string&);
#endif // PARSER_H
