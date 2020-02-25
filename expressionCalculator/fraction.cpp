#include "fraction.h"
fraction::fraction(const string& line)
{
    try{
    string temp(line.substr(1));
    if(temp.size()>=10){
        throw 1;
    }
    numerator = atoi(temp.c_str());
    denominator = pow10(temp.size());
    reduce();
    }
    catch(...){
        std::cout<<"DECIMAL TOO BIG,SETTING FRACTION to 1"<<std::endl;
        *this = fraction(1);
    }
}

void fraction::set(const int x, const int y)
{
    numerator=x;
    denominator=y;
    reduce();
}

int fraction::getDenominator()const
{
    return denominator;
}

int fraction::getNumerator()const
{
    return numerator;
}

fraction& fraction::operator+=(const fraction& other)
{
    *this=*this+other;
    return *this;
}

fraction& fraction::operator*=(const fraction& other)
{
    *this=*this*other;
    return *this;
}

fraction& fraction::operator-=(const fraction& other)
{
    *this=*this-other;
    return *this;
}

fraction& fraction::operator/=(const fraction& other)
{
    *this=*this/other;
    return *this;
}

ostream& operator<<(ostream& out,const fraction& theFraction)
{
    out<<theFraction.numerator<<'/'<<theFraction.denominator;
    return out;
}

fraction operator+(const fraction& x,const fraction& y)
{
    int num = x.numerator*y.denominator+y.numerator*x.denominator;
    int denom = x.denominator*y.denominator;
    return fraction(num,denom);
}

fraction operator-(const fraction& x,const fraction& y)
{
    int num = x.numerator*y.denominator-y.numerator*x.denominator;
    int denom = x.denominator*y.denominator;
    return fraction(num,denom);
}

fraction operator*(const fraction&x,const fraction&y)
{
    int num = x.numerator*y.numerator;
    int denom = x.denominator*y.denominator;
    return fraction(num,denom);
}

fraction operator/(const fraction& x,const fraction& y)
{
    int num = x.numerator*y.denominator;
    int denom = y.numerator*x.denominator;
    return fraction(num,denom);
}

istream& operator>>(istream& in,fraction& theFraction)
{
    theFraction = fraction();
    char junk;
    if(&in == &std::cin){
        std::cout<<"ENTER numerator and denominator: ";
        in>>theFraction.numerator>>junk>>theFraction.denominator;
    }
    else{
        in>>theFraction.numerator;
        if(in.peek()=='/')
            in>>theFraction.denominator;
    }
    theFraction.reduce();
    return in;
}

void fraction::reduce(){
    int div  = gcd(numerator,denominator);
    numerator/=div;
    denominator/=div;
    if(denominator<0){
        numerator*=-1;
        denominator*=-1;
    }
}

int fraction::gcd(int p, int q){
    return q==0?p:gcd(q,p%q);
}
