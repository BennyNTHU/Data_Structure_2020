//EECS2040 Data Structure Hw #1 (Chapter 1, 2 of textbook) 
//due date 4/8/2021 by SNo, 
//106061218, Cheng-En Lee
//Part 2, problem 1

#include <iostream>
#include <algorithm>
#include <math.h>
#include "polynomial.h"
using namespace std;

int main(void)
{
    Polynomial P, Q;

    cout << "enter polynomial P: " << endl; 
    cin >> P;
    cout << "P=" << P << endl;
    cout << "enter polynomial Q";
    cin >> Q;
    cout << "Q=" << Q << endl;

    cout << "deg(P)=" << P.LeadExp() << endl;
    cout << "coefficient of exponents 1 in P=" << P.Coef(1) << endl;
    cout << "P(1) = " << P.Eval(1) << endl;

    Polynomial R = P.Add(Q);
    cout << "R=P+Q=" << R << endl;

    Polynomial S = P.Mult(Q);
    cout << "S=P*Q=" << S << endl;
    
    return 0;
}