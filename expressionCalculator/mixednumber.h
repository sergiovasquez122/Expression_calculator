#ifndef MIXEDNUMBER_H
#define MIXEDNUMBER_H
#include "fraction.h"
using std::getline;
class mixedNumber
{
public:
    mixedNumber(const int& wholePart=0,const int& num=0,const int& denom=1)
        :theInteger(wholePart),theFract(num,denom){}
    mixedNumber(const string& line);
    mixedNumber(const double&);
    double convertToDouble();
    friend ostream& operator<<(ostream&,const mixedNumber&);
    friend istream& operator>>(istream&,mixedNumber&);
    friend mixedNumber operator+(const mixedNumber&,const mixedNumber&);
    friend mixedNumber operator-(const mixedNumber&,const mixedNumber&);
    friend mixedNumber operator /(const mixedNumber&,const mixedNumber&);
    friend mixedNumber operator*(const mixedNumber&,const mixedNumber&);
    friend string to_string(const mixedNumber&);
private:
    void convertToImproper();
    int theInteger;
    fraction theFract;
};

#endif // MIXEDNUMBER_H
