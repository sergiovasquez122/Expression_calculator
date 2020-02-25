#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include "term.h"

class polynomial
{
public:
    polynomial();
    ~polynomial();
    polynomial(const polynomial &p);
    polynomial(const string& );
    void polynomialExpansion(const int& num);
    polynomial& operator=(const polynomial &p);
    polynomial& operator+=(const polynomial& p);
    polynomial& operator-=(const polynomial&);
    polynomial& operator*=(const polynomial&);
    double operator()(double x);
    polynomial operator()(const polynomial& );
    polynomial& operator-();
    friend
    polynomial operator+(const polynomial& a, const polynomial &b);
    friend
    polynomial operator-(const polynomial& a, const polynomial &b);
    friend
    polynomial operator*(const polynomial& a, const polynomial &b);
    friend
    ostream& operator<<(ostream& out, const polynomial &p);
    friend
    istream& operator>>(istream& in, polynomial &p);
    friend
    string to_string(const polynomial&);
    void derive();
private:
    std::vector<term> poly;
    void copy(const polynomial& p);
    void deleteAll();
    void order();
    void combineLikeTerms();
    void reduce();
};

polynomial compute(const polynomial&,const char&,const polynomial&);
#endif // POLYNOMIAL_H
