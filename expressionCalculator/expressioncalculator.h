#ifndef EXPRESSIONCALCULATOR_H
#define EXPRESSIONCALCULATOR_H
#include "fraction.h"
#include "mixednumber.h"
#include "polynomial.h"
#include "term.h"
#include <fstream>
#include <vector>
#include <regex>
class expressionCalculator
{
public:
    expressionCalculator();
    void determineMode(vector<string>&cmdLine);
    void record(string& line);
    void execute(string& line);
    void operator()(const string &);
    void operator [](const string&);
    void startCalculator(const string &line);
    void let(const string&);
    void print(const string&);
    void eval(const string&);
    void setExpression(const string&);
    void clearScreen(const string&);
    void expansion(const string&);
    void functionComposition(const string& line);
    void derive(const string&);
    void save(const string&);
    void load(const string&);
    void helpScreen();
private:
    using fptr = void (expressionCalculator::*)(const string&);
    struct command{
        regex validExpression;
        fptr theFunction;
        command(const regex& theReg,const fptr& theFun){
            validExpression = theReg;
            theFunction = theFun;
        }
    };
    vector<polynomial> expressions;
    vector<command> commands;
    void defaultCase();
    void initializeCommands(vector<command>&);
};

void trim(string& line);
void sanitize(string&);
bool repeat(char*, string&);
#endif // EXPRESSIONCALCULATOR_H
