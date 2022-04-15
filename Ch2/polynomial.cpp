//EECS2040 Data Structure Hw #1 (Chapter 1, 2 of textbook) 
//due date 4/8/2021 by SNo, 
//106061218, Cheng-En Lee
//Part 2, problem 1

#include <iostream>
#include <algorithm>
#include "polynomial.h"
using namespace std;

Polynomial::Polynomial()    // construct the polynomial p(x)=0
{
    terms = 0;
    capacity = 1;
    termArray = (Term *)calloc(capacity, sizeof(Term)); // allocate new memory
    termArray[0].coef = 0;  // initialization
    termArray[0].exp = 0;
}

Polynomial::Polynomial(Term* t , int degree)    // construct a polynomial via specific initialization
{
    terms = degree;
    capacity = degree;
    termArray = (Term *)calloc(capacity, sizeof(Term)); // allocate new memory
    copy(t, t+degree, termArray);
    free(t);
}

Polynomial::~Polynomial()   // destructor
{
    free(termArray);
}

int Polynomial::Coef(int e)  // return the coefficient of exponents e in *this 
{
    for (int i = 0; i < terms; i++) 
	{
        if (termArray[i].exp == e)
            return termArray[i].coef;
    }
    return 0;
}  

int Polynomial::LeadExp() // return the degree of *this
{
    double c[terms];
    for (int i = 0; i < terms; i++) 
        c[i] = termArray[i].coef;
    
    return *max_element(c, c+terms);
}

float Polynomial::Eval(float f)   //Evaluate p(f), the polynomial *this at f and return the results
{
    double value = 0;
    for (int i = 0; i < terms; i++)
        value += termArray[i].coef * pow(f, termArray[i].exp);
    
    return value;
}

void Polynomial::NewTerm(const float theCoeff, const int theExp)    // Add a new term to the end of termArray
{
    if (terms == capacity)     // termArray (of c) is full
    {
        capacity *= 2;         // double the capacity of termArray
        Term *temp = new Term[capacity];  
        copy(termArray, termArray + terms, temp);
        delete [] termArray ;  // delete allocated old memory             
        termArray = temp;
    }
    termArray[terms].coef = theCoeff;
    termArray[terms++].exp = theExp;
}

Polynomial Polynomial::Add(Polynomial b)
{
    Polynomial c;           // Initialize
    int aPos = 0, bPos = 0; // Initialize index of a and b

    while ((aPos < terms) && (bPos < b.terms))
    {
        if (termArray[aPos].exp == b.termArray[bPos].exp) 
        {
            float t = termArray[aPos].coef + b.termArray[bPos].coef;
            if (t) c.NewTerm(t, termArray [aPos].exp);
            aPos++; 
            bPos++;
        }
        else if (termArray[aPos].exp < b.termArray[bPos].exp) 
        {
            c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
            bPos++;
        }
        else 
        {
            c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
            aPos++;
        }
    }
    //add in remaining terms of *this
    for ( ; aPos < terms ; aPos++)  //output the remaining terms
        c.NewTerm (termArray[aPos].coef, termArray[aPos].exp);

    //add in remaining terms of b
    for ( ; bPos < b.terms ; bPos++)    //output remaining terms
        c.NewTerm (b.termArray[bPos].coef, b.termArray[bPos].exp);

    return c;
}

Polynomial Polynomial::Mult(Polynomial b)   //return the product of *this and poly
{
    Polynomial c;           // Initialize
    int aPos = 0, bPos = 0; // Initialize index of a and b

    for(; aPos<terms; aPos++)
    {
        Polynomial buff;    // use distribution law to expand
        for(; bPos<b.terms; bPos++)
            buff.NewTerm (termArray[aPos].coef * b.termArray[bPos].coef, 
                          termArray[aPos].exp + b.termArray[bPos].exp);
        c = c.Add(buff);
        bPos = 0;           // Reset the index of b
        buff.~Polynomial(); // Call the destructor
    }

    return c;
}

istream& operator >> (istream& in, Polynomial& poly)    
{
    int deg, e, c = 0;  // For construct terms
    
	cout<<"The number of terms: ";
    in >> deg;

    Term t[deg];        // term array
    for (int i=0; i<deg; i++)   // enter the terms
    {
        cout<<"enter the power: ";
        in >> e;
        cout<<"enter the coefficient: ";
        in >> c;
        t[i] = Term(e,c);
    }

    poly = Polynomial(t, deg);  // note that don't use "const Polynomial" in line 131
    return in;
}

ostream& operator << (ostream& out, const Polynomial& poly)
{
	if (poly.terms == 0) 
    {
        out << "0\n";
        return out;
    }
    else
    {
        for (int i = 0; i < poly.terms; i++)
            if (i != poly.terms-1)  // not the last term
                if (poly.termArray[i].get_exp()==0) // Constant term
                    out << poly.termArray[i].get_coef() << "+";
                else
                    out << poly.termArray[i].get_coef() << "x^" << poly.termArray[i].get_exp() << "+";
            else    // last term
                if (poly.termArray[i].get_exp()==0) // Constant term
                    out << poly.termArray[i].get_coef();
                else
                    out << poly.termArray[i].get_coef() << "x^" << poly.termArray[i].get_exp();

        return out;
    }
}

Polynomial & Polynomial::operator=(const Polynomial &poly)
{
    capacity = poly.capacity;
    terms = poly.terms;
    termArray = poly.termArray;

    return *this;
}
