#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>
#include <sstream>
#include <cmath>
using std::stringstream;
using std::ostream;
using std::istream;
using std::cout;
using std::string;
class fraction
{
public:
    fraction(int num = 0,int denom = 1):numerator(num),denominator(denom){reduce();}
    fraction(const fraction&)  = default;
    fraction& operator=(const fraction& other) = default;
    ~fraction() = default;
    //Mutators
    fraction& operator+=(const fraction& other);
    fraction& operator*=(const fraction& other);
    fraction& operator-=(const fraction& other);
    fraction& operator/=(const fraction& other);
    fraction(const string& line);
    void set(const int x = 0,const int y=1);
    //accessors
    int getDenominator() const;
    int getNumerator() const;
    int& getDenominator(){return denominator;}
    int& getNumerator(){return numerator;}
    //friends
    friend ostream& operator<<(ostream&,const fraction&);
    friend istream& operator>>(istream&,fraction&);
    friend fraction operator+(const fraction&,const fraction&);
    friend fraction operator-(const fraction&,const fraction&);
    friend fraction operator*(const fraction&,const fraction&);
    friend fraction operator/(const fraction&,const fraction&);
private:
    void reduce();
    int gcd(int p,int q);
    int numerator,denominator;
};
#endif // FRACTION_H
