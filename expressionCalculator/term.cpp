#include "term.h"

term::term(double c, double p)
{
    coeff = c;
    power = p;
}

term::~term()
{
    deleteMe();
}

term::term(const term &other)
{
    copy(other);
}

term& term::operator=(const term &other)
{
    if(this != &other)
    {
        deleteMe();
        copy(other);
    }
    return *this;
}

double term::operator()(double x)
{
    return coeff * pow(x,power);
}

term& term::operator+=(const term &other)
{
    if(power == other.power)
        coeff += other.coeff;
    return *this;
}
term& term::operator*=(double x)
{
    coeff *= x;
    return *this;
}

term& term::operator-=(const term& other){
    if(power == other.power)
        coeff -= other.coeff;
    return *this;
}

term& term::operator*=(const term& other){
    coeff*=other.coeff;
    power+=other.power;
    return *this;
}

void term::copy(const term &other)
{
    coeff = other.coeff;
    power = other.power;
}

term term::composition(const term &x){
    //I AM A CONSTANT EXPRESSION, RETURN MYSELF
    if(x.power<1)
        return term(coeff,power);
    //DO THE ALGEBRA
    term ans=x;
    ans.power*=power;
    ans.coeff = pow(ans.coeff,power);
    ans.coeff*=coeff;
    return ans;
}

term term::operator ()(const term& x){
    return composition(x);
}

void term::deleteMe()
{
    coeff = power = 0;
}

double term::getPower() const
{
    return power;
}

double term::getCoeff() const
{
    return coeff;
}

double& term::getCoeff(){
    return coeff;
}

double& term::getPower(){
    return power;
}

void term::set(double c, double p)
{
    coeff = c;
    power = p;
}

bool operator<(const term& a, const term &b)
{
    return ((a.power == b.power) && (a.coeff < b.coeff))
            ||
            (a.power < b.power);
}

bool operator<=(const term& a, const term &b)
{
    return ((a.power == b.power) && (a.coeff <= b.coeff))
            ||
            (a.power <= b.power);
}

bool operator==(const term& a, const term &b)
{
    return ((a.power == b.power) && (a.coeff == b.coeff));
}

bool operator!=(const term& a, const term &b)
{
    return ((a.power == b.power) && (a.coeff != b.coeff))
            ||
            (a.power != b.power);
}

bool operator>=(const term& a, const term &b)
{
    return ((a.power == b.power) && (a.coeff >= b.coeff))
            ||
            (a.power >= b.power);
}

bool operator>(const term& a, const term &b)
{
    return ((a.power == b.power) && (a.coeff > b.coeff))
            ||
            (a.power > b.power);
}

term operator+(const term& a, const term &b)
{
    return (a.power == b.power) ? term(a.coeff+b.coeff,a.power)
                                : term(0);
}

term operator-(const term& a, const term &b)
{
    return (a.power == b.power) ? term(a.coeff-b.coeff,a.power)
                                : term(0);
}

term operator*(const term& a, const term &b)
{
    return term(a.coeff * b.coeff, a.power + b.power);
}

void term::derive(){
    if(power<=0){
        coeff = power = 0;
        return;
    }
    coeff *= power;
    --power;
}

ostream& operator<<(ostream& out, const term &t)
{
    out<<t.coeff<<"X^"<<t.power;
    return out;
}

istream& operator>>(istream& in, term &t)
{
    t.coeff = t.power = 0;
    char junk;
    if(&in==&cin){
        cout<<"ENTER TERM: ";
        if(in>>t.coeff)
        {
            if(toupper(in.peek()) == 'X')
            {
                in>>junk;
                if(in.peek() == '^')
                {
                    in>>junk;
                    in>>t.power;
                }
            }
        }
    }
    else
        if(in>>t.coeff)
        {
            if(toupper(in.peek()) == 'X')
            {
                //We know that the power is atleast equal to 1
                in>>junk;
                t.power =1;
                if(in.peek() == '^')
                {
                    in>>junk;
                    in>>t.power;
                }
            }
            else
                t.power=0;
        }
    return in;
}
