#include "polynomial.h"
#include <sstream>
using std::stringstream;
string to_string(const polynomial& x)
{
    stringstream ss;
    ss<<x;
    return ss.str();
}

polynomial::polynomial(const string &theString)
{
    stringstream ss(theString);
    while(ss.peek()!=EOF){
        if(ss.peek()==' '|| ss.peek()=='+')
            ss.ignore();
        ss>>*this;
    }
}

polynomial::polynomial()
{
}

polynomial::~polynomial()
{
    deleteAll();
}

polynomial::polynomial(const polynomial &p)
{
    copy(p);
}


void polynomial::derive()
{
    for(size_t i = 0;i<poly.size();++i)
        poly[i].derive();
    reduce();
}

polynomial& polynomial::operator=(const polynomial &other)
{
    if(this != &other)
    {
        deleteAll();
        copy(other);
    }
    return *this;
}

double polynomial::operator()(double x)
{
    double ans = 0;
    for(size_t i = 0; i < poly.size(); ++i)
        ans += poly[i](x);
    return ans;
}

polynomial& polynomial::operator-()
{
    for(size_t i = 0; i < poly.size(); ++i)
        poly[i] *= -1;
    return *this;
}

void polynomial::copy(const polynomial& p)
{
    poly = p.poly;
}

void polynomial::deleteAll()
{
    poly.clear();
}

void polynomial::reduce()
{
    order();
    combineLikeTerms();
}

void polynomial::order()
{
    sort(poly.begin(),poly.end(),[](const term& x,const term& y){
        return x.getPower()>y.getPower();
    });
}

void polynomial::combineLikeTerms()
{
    vector<term> ans;
    term temp;
    if(poly.size()==1)
        return;
    while(!poly.empty())
    {
        temp = poly[0];
        poly.erase(poly.begin(),poly.begin()+1);
        while(!poly.empty()&&(temp.getPower() == poly[0].getPower()))
        {
            temp += poly[0];
            poly.erase(poly.begin(), poly.begin()+1);
        }
        ans.push_back(temp);
    }
    poly = ans;
}

polynomial operator+(const polynomial& a, const polynomial &b)
{
    polynomial ans;
    for(size_t i = 0; i < a.poly.size(); ++i)
        for(size_t j = 0; j < b.poly.size(); ++j)
            if(a.poly[i].getPower() == b.poly[j].getPower())
                ans.poly.push_back(a.poly[i] + b.poly[j]);
    ans.reduce();
    return ans;
}

polynomial operator-(const polynomial& a, const polynomial &b)
{
    polynomial ans;
    for(size_t i = 0; i < a.poly.size(); ++i)
        for(size_t j = 0; j < b.poly.size(); ++j)
            if(a.poly[i].getPower() == b.poly[j].getPower())
                ans.poly.push_back(a.poly[i] - b.poly[j]);
    ans.reduce();
    return ans;
}

polynomial polynomial::operator()(const polynomial& x){
    polynomial ans;
    for(size_t i = 0;i<poly.size();++i){
        for(size_t j = 0;j<x.poly.size();++j)
            ans.poly.push_back(poly[i](x.poly[j]));
    }
    ans.reduce();
    return ans;
}

polynomial operator*(const polynomial& a, const polynomial &b)
{
    polynomial ans;
    for(size_t i = 0; i < a.poly.size(); ++i)
        for(size_t j = 0; j < b.poly.size(); ++j)
            ans.poly.push_back(a.poly[i] * b.poly[j]);
    ans.reduce();
    return ans;
}


ostream& operator<<(ostream& out, const polynomial &p)
{
    if(p.poly.empty())
        out<<0;
    else{
        out<<p.poly[0];
        if(p.poly.size()>1){
            for(size_t i = 1; i <p.poly.size(); ++i){
                if(p.poly[i].getCoeff()>=0)
                    out<<'+'<<p.poly[i];
                else
                    out<<p.poly[i];
            }
        }
    }
    return out;
}


istream& operator>>(istream& in, polynomial &p)
{
    term theTerm;
    p.poly.clear();
    while(in>>theTerm)
        p.poly.push_back(theTerm);
    p.reduce();
    return in;
}

polynomial compute(const polynomial& x,const char& op,const polynomial& y){
    polynomial ret(x);
    switch (op) {
    case '+':
        ret = x+y;
        break;
    case '-':
        ret = x-y;
        break;
    case '*':
        ret = x*y;
        break;
    }
    return ret;
}

//NEED TO FIGURE OUT
void polynomial::polynomialExpansion(const int &num){
    //anything raised to the 0 power is 1
    if(num==0){
        poly.clear();
        poly.push_back(term(1));
        return;
    }
    //The item raised to itself is still itself
    else if(num==1)
        return;
    //DISTRIBUTE
    polynomial answer(*this);
    for(size_t i = 0;i<num-1;++i){
        answer = *this*answer;
    }
    poly = answer.poly;
    reduce();
}

polynomial& polynomial::operator*=(const polynomial& x)
{
    polynomial temp(*this);
    *this = temp*x;
    return *this;
}
