#include "mixednumber.h"
string to_string(const mixedNumber& theMixed)
{
    stringstream ss;
    ss<<theMixed;
    return ss.str();
}

mixedNumber::mixedNumber(const double &theNumber){
    stringstream ss;
    ss<<theNumber;
    string temp(ss.str());
    *this = mixedNumber(temp);
}

mixedNumber::mixedNumber(const string& line)
{
    stringstream ss(line);
    ss>>*this;
}

void mixedNumber::convertToImproper()
{
    bool isNegative = (theInteger<0||theFract.getNumerator()<0);
    theInteger*=theFract.getDenominator();
    theInteger = abs(theInteger)+abs(theFract.getNumerator());
    int temp;
    isNegative ? temp = -1*theInteger: temp = theInteger;
    theFract.set(temp,theFract.getDenominator());
    theInteger =  0;
}

double mixedNumber::convertToDouble(){
    convertToImproper();
    return (double)theFract.getNumerator()/theFract.getDenominator();
}

ostream& operator<<(ostream& out,const mixedNumber& theMixed)
{
    //EXPRESSION IS ZERO PRINT IT
    if(theMixed.theInteger==0 && theMixed.theFract.getNumerator()==0){
        cout<<theMixed.theInteger<<' ';
    }
    //WE MUST DECIDE WHAT TO PRINT
    else{
        //If we know we have an integer value not equal to zero print it
        if(theMixed.theInteger)
            out<<theMixed.theInteger<<' ';
        //If we have a fractional part print it
        if(theMixed.theFract.getNumerator())
            out<<theMixed.theFract;
    }
    return out;
}

istream& operator>>(istream& in,mixedNumber& theMixed)
{
    if(&in==&std::cin){
        //DO console stuff
    }
    else{
        //reset the content
        theMixed = mixedNumber();
        //Will need to know different case, case for decimal,only integer and for only fraction
        in>>theMixed.theInteger;
        //Doing case where decimal,  assume form of [0-9]+[.][0-9]+
        if(in.peek()=='.'){
            string content;
            content.push_back(in.get());
            while(isdigit(in.peek()))
                content.push_back(in.get());
            theMixed.theFract = fraction(content);
            string line;
            in.seekg(0);
            getline(in,line);
            if(line.find("-0.")<line.size())
                theMixed.theFract=-1*theMixed.theFract;
        }
        //Doing where only case is for fraction
        else if(in.peek()=='/')
        {
            in.ignore();
            theMixed.theFract.set(theMixed.theInteger);
            in>>theMixed.theFract.getDenominator();
            theMixed.theInteger = 0;
        }
        //Assume is in mixed number form
        else {
            //Ignore the space
            in.ignore();
            in>>theMixed.theFract.getNumerator();
            //Ignore the /
            in.ignore();
            in>>theMixed.theFract.getDenominator();
        }
    }
    return in;
}

mixedNumber operator+(const mixedNumber& x,const mixedNumber& y)
{
    mixedNumber ret(x);
    ret.theInteger+=y.theInteger;
    ret.theFract+=y.theFract;
    ret.convertToImproper();
    return ret;
}

mixedNumber operator-(const mixedNumber& x,const mixedNumber& y)
{
    mixedNumber ret(x);
    ret.theInteger-=y.theInteger;
    ret.theFract-=y.theFract;
    ret.convertToImproper();
    return ret;
}

mixedNumber operator /(const mixedNumber& x,const mixedNumber& y)
{
    mixedNumber ret(x);
    ret.theInteger/=y.theInteger;
    ret.theFract/=y.theFract;
    ret.convertToImproper();
    return ret;
}

mixedNumber operator*(const mixedNumber& x,const mixedNumber& y)
{
    mixedNumber ret(x);
    ret.theInteger*=y.theInteger;
    ret.theFract*=y.theFract;
    ret.convertToImproper();
    return ret;
}
