#include "expressioncalculator.h"

expressionCalculator::expressionCalculator()
{
    initializeCommands(commands);
    for(u_int i = 0;i<26;++i)
        expressions.push_back(polynomial());
}

void expressionCalculator::initializeCommands(vector<command> &commands){
    //Let expression equal to polynomial
    commands.push_back(command(regex("LET [A-Z] = (-?[0-9]+(X[^][0-9]+))([+-][0-9]+(X[^][0-9]+))*"),&expressionCalculator::let));
    //Print out certain expression
    commands.push_back(command(regex("PRINT [A-Z]"),&expressionCalculator::print));
    //evaluate fraction or decimal or mixedNumer
    commands.push_back(command(regex("EVAL [A-Z][(](-?[0-9]+[/][1-9][0-9]*|-?[0-9]+([.][0-9]+)?|-?[0-9]+ ([0-9]+/[1-9][0-9]*))*[)]"),&expressionCalculator::eval));
    //computes and save expression
    commands.push_back(command(regex("[A-Z] = [A-Z][+*-][A-Z]"),&expressionCalculator::setExpression));
    //Derive the equation
    commands.push_back(command(regex("[A-Z] = [A-Z][']+"),&expressionCalculator::derive));
    //save
    commands.push_back(command(regex("SAVE [A-Z]+[0-9]*([.]EXP)? *"),&expressionCalculator::save));
    //load
    commands.push_back(command(regex("LOAD [A-Z]+[0-9]*([.]EXP)? *"),&expressionCalculator::load));
    //clearScreen
    commands.push_back(command(regex("CLEAR *"),&expressionCalculator::clearScreen));
    //expansion
    commands.push_back(command(regex("[A-Z] = [(](-?[0-9]+(X[^][0-9]+))([+-][0-9]+(X[^][0-9]+))*[)][^][0-9]+"),
                               &expressionCalculator::expansion));
    //FUNCTION DECOMPOSITION
    commands.push_back(command(regex("[A-Z] = [A-Z][(][A-Z][)]"),&expressionCalculator::functionComposition));
}

void expressionCalculator::clearScreen(const string &userinput)
{
    for(u_int i = 0;i<100;++i)
        cout<<endl;
}

void expressionCalculator::startCalculator(const string &userinput){
    bool valid=false;
    for(u_int i = 0;i<commands.size();++i){
        if(regex_match(userinput,commands[i].validExpression)){
            fptr func = commands[i].theFunction;
            (this->*func)(userinput);
            valid = true;
            break;
        }
    }
    if(!valid)
        defaultCase();
}

void expressionCalculator::save(const string &line){
    string filename(line);
    trim(filename);
    //ERASE 'SAVE'
    filename.erase(0,4);
    if(filename.find('.')==string::npos)
        filename.append(".EXP");
    ifstream file(filename);
    if(file.fail())
    {
        ofstream out(filename);
        for(u_int i = 0;i<expressions.size();++i)
            out<<expressions[i]<<endl;
    }
    else{
        cout<<"FILE "<<filename<<" EXISTS"<<endl;
        cout<<"PRESS ENTER TO CONTINUE OVERWRITE,ANY OTHER KEY TO EXIT "<<endl;
        string userinput;
        getline(cin,userinput);
        if(!userinput.empty())
            return;
        ofstream out(filename);
        for(u_int i = 0;i<expressions.size();++i)
            out<<expressions[i]<<endl;
    }
}

void expressionCalculator::load(const string &line){
    string filename(line);
    //ERASE 'LOAD'
    if(line.find("LOAD")!=string::npos)
        filename.erase(0,4);
    trim(filename);
    if(filename.find('.')==string::npos)
        filename.append(".EXP");
    ifstream file(filename);
    if(file.fail()){
        cout<<"FILE DOES NOT EXIST"<<endl;
        exit(1);
    }
    else{
        expressions.clear();
        string theLine;
        while(getline(file,theLine)){
            stringstream ss(theLine);
            polynomial temp;
            ss>>temp;
            expressions.push_back(temp);
        }
    }
}

void expressionCalculator::operator ()(const string& line){
    startCalculator(line);
}

void expressionCalculator::operator [](const string& line)
{
    print(line);
}

//ASSUMES EXPRESSION IN THE FORM OF PRINT [A-Z]
void expressionCalculator::print(const string & line){
    int pos = line.find_last_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    cout<<line[pos]<<" = "<<expressions[line[pos]-'A']<<endl;
}

//ASSUMES EXPRESSION IN THE FORM OF [A-Z] = [A-Z][+/*][A-Z]
void expressionCalculator::setExpression(const string &line)
{
    string temp = line.substr(line.find_last_of(' ')+1);
    expressions[line[0]-'A'] = compute(expressions[temp[0]-'A'],temp[1],expressions[temp[2]-'A']);
    cout<<line[0]<<" = "<<expressions[line[0]-'A']<<endl;
}

//ASSUMES EXPRESSION IN THE FORM OF [A-Z] = [A-Z][']+
void expressionCalculator::derive(const string &line)
{
    string valueToBeDerived = line.substr(line.find_last_of(' ')+1);
    // G''' means totalDeriatives = 3
    u_int totalDerivatives = valueToBeDerived.substr(valueToBeDerived.find_first_of('\'')).size();
    //We do not want to modify the content of the expression so use temp
    polynomial temp(expressions[valueToBeDerived[0]-'A']);
    for(u_int i =0;i<totalDerivatives;++i)
        temp.derive();
    expressions[line[0]-'A'] = temp;
    cout<<line[0]<<" = "<<expressions[line[0]-'A']<<endl;
}

//ASSUME THE EXPRESSION IN THE FORM EVAL [A-Z](VALID MIXED NUMBER)
void expressionCalculator::eval(const string &line)
{
    //[A-Z](valid Number)
    string theExpression(line.substr(line.find_last_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ")));
    //valid number
    string valueToCompute(theExpression.substr(theExpression.find('(')+1,theExpression.find(')')));
    valueToCompute.pop_back();
    //CONVERT STRING TO DOUBLE THEN EVALUATE EXPRESSION
    mixedNumber temp(expressions[theExpression[0]-'A'](mixedNumber(valueToCompute).convertToDouble()));
    cout<<theExpression<<" = "<<temp<<endl;
}

void expressionCalculator::let(const string &line)
{
    //F = 2x^2.....
    string theExpression(line.substr(line.find_first_of(' ')+1));
    string poly(theExpression.substr(theExpression.find_last_of(' ')+1));
    expressions[theExpression[0]-'A'] = polynomial(poly);
    cout<<theExpression[0]<<" = "<<expressions[theExpression[0]-'A']<<endl;
}

//A = (2x^2)^3
void expressionCalculator::expansion(const string &line)
{
    //2x^2
    string poly = line.substr(line.find_first_of('(')+1);
    poly.erase(poly.find(')'));
    //find the power and extract it
    string thePower = line.substr(line.find_last_of('^')+1);
    int power;
    stringstream ss(thePower);
    ss>>power;
    expressions[line[0]-'A'] = polynomial(poly);
    //ACCESS THE power
    expressions[line[0]-'A'].polynomialExpansion(power);
    cout<<line[0]<<" = "<<expressions[line[0]-'A']<<endl;
}

//ASSUMES EXPRESSION IS IN THE FORM OF F = G(H)
void expressionCalculator::functionComposition(const string &line)
{
    //G(H)
    string theComposition(line.substr(line.find_last_of(' ')+1));
    polynomial ans;
    ans =  expressions[theComposition[0]-'A'](expressions[theComposition[2]-'A']);
    //GET THE ELEMENT THAT NEEDS TO BE MODIFIED
    expressions[line[0]-'A'] = ans;
    cout<<line[0]<<" = "<<expressions[line[0]-'A']<<endl;
}

void expressionCalculator::defaultCase(){
    cout<<"INVALID STATEMENT"<<endl;
}

void trim(string &line){
    u_int pos;
    while((pos = line.find(' '))<line.size())
        line.erase(pos,1);
}

void sanitize(string& line)
{
    for(u_int i = 0;i<line.length();++i){
        if(line[i]==' ')
            line.erase(i--,1);
        line[i] = toupper(line[i]);
    }
}

bool repeat(char* title,string& line){
    cout<<title;
    getline(cin,line);
    return !line.empty();
}

void expressionCalculator::determineMode(vector<string> &cmdLine)
{
    if(cmdLine.size()==1)
    {
        string userinput;
        while (repeat("COMMAND: ",userinput)) {
            transform(userinput.begin(),userinput.end(),userinput.begin(),::toupper);
            startCalculator(userinput);
        }
    }
    else if(cmdLine.size()==2){
        if(cmdLine[1]=="/H"||cmdLine[1]=="/?")
            helpScreen();
        else{
            load(cmdLine[1]);
            string userinput;
            while (repeat("COMMAND: ",userinput)) {
                transform(userinput.begin(),userinput.end(),userinput.begin(),::toupper);
                startCalculator(userinput);
            }
        }
    }
    else if(cmdLine.size()==3){
        if(cmdLine[1]=="EXECUTE")
            execute(cmdLine[2]);
        else if(cmdLine[1]=="RECORD")
            record(cmdLine[2]);
        else
        {
            cout<<"INVALID STATEMENT"<<endl;
        }
    }
    else{
        cout<<"TOO MANY PARAMETERS!"<<endl;
        exit(0);
    }
}

void expressionCalculator::helpScreen()
{
    cout<<"WELCOME TO THE EXPRESSION CALCULATOR!"<<endl;
    cout<<"THERE ARE 26 POLYNOMIALS, THERE ARE REPRESENTED BY THE LETTERS [A-Z]"<<endl;
    cout<<"HERE OUR THE POSSIBLE COMMANDS FOR THE EXPRESSION CALC"<<endl;
    cout<<"LET [A-Z] = polynomial, CHANGES THE CONTENT OF DESIRED POLYNOMIAL"<<endl;
    cout<<"EVAL [A-Z](MIXED NUMBER | FRACTION | DECIMAL),EVALUATES EXPRESSION"<<endl;
    cout<<"PRINT [A-Z],PRINT THE POLYNOMIAL DESIRED"<<endl;
    cout<<"SAVE filename.exp to save content"<<endl;
    cout<<"LOAD filename.exp to load content"<<endl;
}

void expressionCalculator::record(string &filename){
    transform(filename.begin(),filename.end(),filename.begin(),::toupper);
    if(filename.find('.')==string::npos)
        filename.append(".SPT");
    ifstream in(filename);
    if(!in.fail()){
        cout<<"THE FILE "<<filename<<" EXISTS"<<endl;
        cout<<"PRESS ENTER TO OVERWRITE,ANY OTHER KEY TO DISALLOW: ";
        string userinput;
        getline(cin,userinput);
        if(!userinput.empty())
            exit(0);
    }
    ofstream out(filename);
    string expression;
    while(repeat("COMMAND: ",expression))
        out<<expression<<endl;
}

void expressionCalculator::execute(string& filename)
{
    transform(filename.begin(),filename.end(),filename.begin(),::toupper);
    if(filename.find('.')==string::npos)
        filename.append(".SPT");
    else{
        if(filename.find('.')+1==filename.size()||filename.find("SPT")==string::npos){
            cout<<"MODIFIYING TO SCRIPT FILE TYPE"<<endl;
            filename.replace(filename.find('.'),string::npos,".SPT");
        }
    }
    ifstream in(filename);
    if(in.fail()){
        cout<<"FILE DOES NOT EXIST"<<endl;
        exit(0);
    }
    string line;
    while(getline(in,line)){
        transform(line.begin(),line.end(),line.begin(),::toupper);
        cout<<line<<endl;
        startCalculator(line);
    }
}
