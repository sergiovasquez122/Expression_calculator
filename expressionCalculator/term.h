#ifndef TERM_H
#define TERM_H
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <sstream>
using namespace std;

class term
{
    public:
        term(double c = 1, double p = 0);
        ~term();
        term(const term &other);
        term& operator=(const term &other);
        term& operator+=(const term &other);
        term& operator*=(const term&);
        term& operator-=(const term&);
        double operator()(double x);
        term& operator*=(double x);
        double getPower() const;
        double getCoeff() const;
        double& getCoeff();
        double& getPower();
        term composition(const term&x);
        term operator()(const term&);
        void derive();
        void set(double c = 1, double p = 0);


        friend
        bool operator<(const term& a, const term &b);

        friend
        bool operator<=(const term& a, const term &b);

        friend
        bool operator==(const term& a, const term &b);

        friend
        bool operator!=(const term& a, const term &b);

        friend
        bool operator>=(const term& a, const term &b);

        friend
        bool operator>(const term& a, const term &b);

        friend
        term operator+(const term& a, const term &b);

        friend
        term operator-(const term& a, const term &b);

        friend
        term operator*(const term& a, const term &b);

        friend
        ostream& operator<<(ostream& out, const term &t);

        friend
        istream& operator>>(istream& in, term &t);
    private:
        double coeff, power;

        void copy(const term &other);
        void deleteMe();
};

#endif // TERM_H
