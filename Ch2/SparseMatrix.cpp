//EECS2040 Data Structure Hw #1 (Chapter 1, 2 of textbook) 
//due date 4/8/2021 by SNo, 
//106061218, Cheng-En Lee
//Part 2, problem 2

#include <iostream>
#include <algorithm>
#include "SparseMatrix.h"
using namespace std;

SparseMatrix::SparseMatrix(int r, int c, int t) // constructor. r is #row, c is #col, t is #non-zero terms
{
    rows = r;
    cols = c;
    terms = t;
    capacity = terms;
    smArray = (MatrixTerm *)calloc(capacity, sizeof(MatrixTerm)); // allocate a new memory
}

SparseMatrix::SparseMatrix(const SparseMatrix &b) // constructor with another matrix
{
    rows = b.rows;
    cols = b.cols;
    terms = b.terms;
    capacity = b.capacity;
    smArray = (MatrixTerm *)calloc(capacity, sizeof(MatrixTerm));

	for (int i = 0; i < terms; i++) 
	{ 
		smArray[i].row = b.smArray[i].row; 
        smArray[i].col = b.smArray[i].col;
        smArray[i].value = b.smArray[i].value;
	} 
}

SparseMatrix::~SparseMatrix()   // destructor
{
    free(smArray);
}

void SparseMatrix::StoreSum(const int sum, const int r, const int c)    // add a new term
{
    if (sum != 0) 
    {
        if (terms == capacity)
            ChangeSize1D(2*capacity); 
        smArray[terms].row = r;
        smArray[terms].col = c;
        smArray[terms++].value = sum;
    }
}

void SparseMatrix::ChangeSize1D(const int newSize)    // change the array size to newSize
{ 
    if (newSize < terms) 
        throw "New size must be >= number of terms";

    MatrixTerm *temp = new MatrixTerm[newSize]; // new array
    copy(smArray, smArray + terms, temp);
    delete [] smArray; 

    smArray = temp; // make smArray point to the newly created array
    capacity = newSize;
}

int SparseMatrix::get_terms()   // return the number of terms of *this
{
    int count = 0;
    for (int i=0; i<terms; i++)
        count++;

    return count;
}

SparseMatrix SparseMatrix::FastTranspose()  // Transpose of *this
{
    SparseMatrix b(cols , rows , terms);

    if (terms > 0) 
    {
        int *rowSize = new int[cols];
        int *rowStart = new int[cols];
    
        fill(rowSize, rowSize + cols, 0);   // fill the array with 0
        for (int i = 0 ; i < terms ; i ++)  // calculate the row size of the new matrix
            rowSize[smArray[i].col]++;

        // calculate the starting array index of each row of the new matrix
        rowStart[0] = 0;
        for (int i = 1 ; i < cols ; i++) 
            rowStart[i] = rowStart[i-1] + rowSize[i-1];

        for (int i = 0 ; i < terms ; i++)
        {
            int j = rowStart[smArray[i].col];
            b.smArray[j].row= smArray[i].col;
            b.smArray[j].col = smArray[i].row;
            b.smArray[j].value = smArray[i].value;
            rowStart[smArray[i].col]++;
        }

        delete [] rowSize;
        delete [] rowStart;
    }
    return b;
}

SparseMatrix SparseMatrix::Add(SparseMatrix b)  // return *this+b or throw an exception
{
    int add_terms = 0;  // the number of terms of *this+b
    int same_place = 0; // the number of terms of *this+b which has same row and col index
    int c_index = 0;    // index of c=*this+b

    if (rows != b.rows || cols != b.cols)   // throw exception
        throw "Not the same size!";
    
    // count the terms
    for (int i=0; i<=terms; i++)
    {
        for (int j=0; j<=b.get_terms(); j++)    // if having same row and col index
            if (smArray[i].get_col() == b.smArray[j].get_col() && 
                smArray[i].get_row() == b.smArray[j].get_row())
                same_place++;
    }
    add_terms = terms + b.get_terms() - same_place; // the number of terms of *this+b
    SparseMatrix c(rows, cols, add_terms);  // construct c=*this+b

    // add the terms having same position
    for (int i=0; i<=terms; i++)
        for (int j=0; j<=b.get_terms(); j++)
            if (smArray[i].get_col() == b.smArray[j].get_col() && 
                smArray[i].get_row() == b.smArray[j].get_row())
            {
                c.smArray[c_index++].write_term
                (smArray[i].row, smArray[i].col, smArray[i].value+b.smArray[j].get_value());
            }
    
    // add the remain terms in *this
    for (int i=0; i<terms; i++)
    {
        int count = 0;  // count how many terms have different col and row index with current term of *this
        for (int j=0; j<b.get_terms(); j++)
        {
            if (smArray[i].get_col() != b.smArray[j].get_col() || 
                smArray[i].get_row() != b.smArray[j].get_row()) // have different col and row
                count++;
        }
        if (count==b.get_terms())   // overwrite the term  
            c.smArray[c_index++].write_term(smArray[i].row, smArray[i].col, smArray[i].value);
    }

    // add the remain terms in b
    for (int i=0; i<b.get_terms(); i++)
    {
        int count = 0;  // count how many terms have different col and row index with current term of b
        for (int j=0; j<terms; j++)
        {
            if (b.smArray[i].get_col() != smArray[j].get_col() || 
                b.smArray[i].get_row() != smArray[j].get_row()) // have different col and row
                count++;
        }
        if (count==terms)   // overwrite the term  
            c.smArray[c_index++].write_term
            (b.smArray[i].get_row(), b.smArray[i].get_col(), b.smArray[i].get_value());
    }
    
    return c;
}

SparseMatrix SparseMatrix::Multiply(SparseMatrix b)
{
    if (cols != b.rows) // error handling
        throw "Incompatible matrices";  

    SparseMatrix bXpose = b.FastTranspose( );   // transpose b
    SparseMatrix d (rows, b.cols, 0);  // create the output matrix d
    int currRowIndex = 0,
    currRowBegin = 0,
    currRowA = smArray[0].row;

    // introduce dummy terms for handling boundary condition
    if (terms == capacity) 
        ChangeSize1D(terms + 1);

    // introduce dummy terms for handling boundary condition
    bXpose.ChangeSize1D(bXpose.terms + 1);
    smArray[terms].row = rows;
    bXpose.smArray[b.terms].row = b.cols;
    bXpose.smArray[b.terms].col = -1;

    int sum = 0;
    while (currRowIndex < terms)    // check currRowA is valid
    { 
        int currColB = bXpose.smArray[0].row;
        int currColIndex = 0;
        while (currColIndex <= b.terms) // process B matrix term by term
        { 
            if (smArray[currRowIndex].row != currRowA)  // row end 
            {  
                d.StoreSum(sum,currRowA,currColB);   // store the sum
                sum = 0;     // reset the sum
                currRowIndex = currRowBegin; // rewind the row

                while (bXpose.smArray[currColIndex].row == currColB)
                    currColIndex++;   // skip terms in the curr col

                currColB = bXpose.smArray[currColIndex].row;  // next col
            } 
            else if (bXpose.smArray[currColIndex].row != currColB)  // col end
            {
                d.StoreSum(sum,currRowA,currColB); // output the sum
                sum = 0; // reset the sum
                currRowIndex = currRowBegin; // rewind the row
                currColB = bXpose.smArray[currColIndex].row; // next col
            }
            else 
            {
                if (smArray[currRowIndex].col < bXpose.smArray[currColIndex].col)
                    currRowIndex++;  
                else if (smArray[currRowIndex].col == bXpose.smArray[currColIndex].col) 
                {
                    sum += smArray[currRowIndex].value *
                    bXpose.smArray[currColIndex].value;
                    currRowIndex++;  
                    currColIndex++;
                }
                else    
                    currColIndex++; 
            } 
        } 
        while (smArray[currRowIndex].row == currRowA)
            currRowIndex++; // skip terms in the curr row
            currRowBegin = currRowIndex;  //next row
            currRowA = smArray[currRowIndex].row; //next row
    }
    return d;
}

istream& operator >> (istream& in, const SparseMatrix& b)   // overload >>
{
    int r, c, v = 0;    // the (row, col, value) triple of a term
	cout << "type (row,col,value), seperate with space: " << endl;
    for (int i=0; i<b.terms; i++)
    {
        in >> r >> c >> v;  // enter the triple
        b.smArray[i].write_term(r, c, v);   // overwrite a term
    }
    return in;
}

ostream& operator << (ostream& out, const SparseMatrix& b)  // overload <<
{
    out << "(row,col,value)" << endl;   
	for (int i=0; i<b.terms; i++)   // print the (row, col, value) triple
        out << '(' << b.smArray[i].get_row() << ',' <<  b.smArray[i].get_col()
            << ',' << b.smArray[i].get_value() << ')' << endl;
    return out;
}