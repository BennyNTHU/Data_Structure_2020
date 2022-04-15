//EECS2040 Data Structure Hw #1 (Chapter 1, 2 of textbook) 
//due date 4/8/2021 by SNo, 
//106061218, Cheng-En Lee
//Part 2, problem 1

#ifndef POLYNOMIAL
#define POLYNOMIAL
#include <iostream>
#include <math.h>
using namespace std;

class Polynomial;    //forward declaration

class Term
{
    friend Polynomial;
    private:
        float coef;  //coefficient
        int exp;     //exponent
    public:
        Term() {coef = 0; exp = 0;} // Default constructor
        Term(int e, float c) {exp = e; coef = c;}   // Constructor with input
        float get_coef() {return coef;}             // return the coefficient of a term
        int get_exp() {return exp;}                 // return the exponential of a term
        void write_term(int e, int c) {exp = e; coef = c;}  // overwrite a term
};

class Polynomial 
{
    private:
        Term *termArray;    // array of terms
        int capacity;       //size of termArray
        int terms;          //number of nonzero terms

    public:
        //  Constructor & destructors
        Polynomial();  // construct the polynomial p(x)=0
        Polynomial(Term* t, int degree);    // construct a polynomial via specific initialization
        ~Polynomial();  // destructor

        // member functions for getting attributes
        int Coef(int e);       // return the coefficient of exponents e in *this    
        int LeadExp();         // return the degree of *this
        float Eval(float f);   // Evaluate p(f), the polynomial *this at f and return the results
        void NewTerm(const float theCoeff, const int theExp);   // Add a new term

        // member functions for polynomial adding and multipling
        Polynomial Add(Polynomial poly);    //return the sum of *this and poly
        Polynomial Mult(Polynomial poly);   //return the product of *this and poly

        // operator overload
        friend istream& operator >> (istream& in, Polynomial& poly);          // overload >>
	    friend ostream& operator << (ostream& out, const Polynomial& poly);   // overload <<
        Polynomial& operator=(const Polynomial &);  // overload =
};

istream& operator >> (istream& in, Polynomial& poly);    
ostream& operator << (ostream& out, const Polynomial& poly);

#endif