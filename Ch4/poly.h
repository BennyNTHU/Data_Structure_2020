//EECS2040 Data Structure Hw #3 (Chapter 4 of textbook)
//due date 5/16/2021
//106061218, Cheng-En Lee
//Part 2, problem 2

#ifndef POLY
#define POLY

#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include "node.h"

class Polynomial
{
	private:
		Node* poly;
		void trimZero();

	public:
		Polynomial (); // default constructor
		Polynomial (const Polynomial& a); // copy constructor
		~Polynomial ();   // destructor

		Polynomial operator+ (const Polynomial& b) const;
		Polynomial operator- (const Polynomial& b) const;
		Polynomial operator* (const Polynomial& b) const;

		double Evaluate (double x) const;

		friend std::istream& operator>> (std::istream& in, Polynomial& x);
		friend std::ostream& operator<< (std::ostream& out, Polynomial& x);
		Polynomial& operator= (const Polynomial& a);
};

#endif
