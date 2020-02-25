#include <iostream>
#include <typeinfo>
#include <unistd.h>
#include <iomanip>
#include "expressioncalculator.h"
using namespace std;
bool getLine(const char *title, string &line);
int main(int argc,char** argv)
{
    vector<string> cmdLine;
    for(int i = 0;i<argc;++i){
        cmdLine.push_back(argv[i]);
        sanitize(cmdLine[i]);
    }
    expressionCalculator calc;
    calc.determineMode(cmdLine);
}

bool getLine(const char* title ,string& line){
    cout<<title;
    getline(cin,line);
    return !line.empty();
}
