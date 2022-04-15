//EECS2040 Data Structure Hw #1 (Chapter 1, 2 of textbook) 
//due date 4/8/2021 by SNo, 
//106061218, Cheng-En Lee
//Part 2, problem 2

#ifndef SPARSEMATRIX
#define SPARSEMATRIX
#include <iostream>
#include <math.h>
using namespace std;

class SparseMatrix;

class MatrixTerm    // term of matrix
{
    friend SparseMatrix;
    private:
        int row, col, value;  // a triple representing a term

    public:
        int get_row() {return this->row;}
        int get_col() {return this->col;}
        int get_value() {return this->value;}
        void write_term(int r, int c, int v) {row=r; col=c; value=v;}   // overwrite a term
};

class SparseMatrix  // the matrix *this
{
    private:
        int rows, cols, terms, capacity;
        MatrixTerm *smArray;

    public:
        SparseMatrix(int r, int c, int t);  // constructor. r is #row, c is #col, t is #non-zero terms
        SparseMatrix(const SparseMatrix &b);// constructor with another matrix (so we need not overload =)
        ~SparseMatrix();    // destructor

        void StoreSum(const int sum, const int r, const int c); // add a new term
        void ChangeSize1D(const int newSize);   // change the array size to newSize
        int get_terms();    // return the number of terms of *this

        SparseMatrix FastTranspose();       // Transpose of *this
        SparseMatrix Add(SparseMatrix b);   // return *this+b or throw an exception
        SparseMatrix Multiply(SparseMatrix b);  // return *this*b or throw an exception
        
        friend istream& operator >> (istream& in, const SparseMatrix& b);    // overload >>
	    friend ostream& operator << (ostream& out, const SparseMatrix& b);   // overload <<
};

istream& operator >> (istream& in, const SparseMatrix& b);    
ostream& operator << (ostream& out, const SparseMatrix& b);

#endif