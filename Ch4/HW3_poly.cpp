//EECS2040 Data Structure Hw #3 (Chapter 4 of textbook)
//due date 5/16/2021
//106061218, Cheng-En Lee
//Part 2, problem 2

#include <iostream>
#include <algorithm>
#include <math.h>
#include <cstring>
#include "poly.h"

using namespace::std;

int main(void)
{
    Polynomial P, Q;
    
    cout << "enter polynomial P: " << endl; 
    cin >> P;
    cout << "P=" << P << endl;
    cout << "enter polynomial Q: ";
    cin >> Q;
    cout << "Q=" << Q << endl;

    Polynomial R = P + Q;
    cout << "R=P+Q=" << R << endl;
    R=P-Q;
    cout << "R=P-Q=" << R << endl;
    R=P*Q;
    cout << "R=P*Q=" << R << endl;
    cout << "P(1) = " << P.Evaluate(1) << endl;

    Polynomial S(R);
    cout << "copy constructor S(R)" << S << endl;
    
    return 0;
}