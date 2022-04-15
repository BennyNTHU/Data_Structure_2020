//EECS2040 Data Structure Hw #1 (Chapter 1, 2 of textbook) 
//due date 4/8/2021 by SNo, 
//106061218, Cheng-En Lee
//Part 2, problem 2

#include <iostream>
#include <algorithm>
#include <math.h>
#include "SparseMatrix.h"
using namespace::std;

int main(void)
{
    SparseMatrix b1(3,3,4);
    cin >> b1;
    cout << "The matrix b1=" << b1 << endl;

    SparseMatrix b2(3,3,4);
    cin >> b2;
    cout << "The matrix b2=" << b2 << endl;

    SparseMatrix b3 = b2;
    cout << "The matrix b3=b2 (construct by overloading assignment): " << b3 << endl;

    cout << "Transpose of b1" << b1.FastTranspose() << endl;

    SparseMatrix b4 = b1.Add(b2);
    cout << "b1+b2=" << b4 << endl;

    SparseMatrix b5 = b1.Multiply(b2);
    cout << "b1*b2=" << b5 << endl;

    return 0;
}