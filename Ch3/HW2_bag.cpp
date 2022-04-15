//EECS2040 Data Structure Hw #2 (Chapter 3 of textbook)
//due date 4/17/2021
//106061218, Cheng-En Lee
//Part 2, problem 2

#include <iostream>
#include <algorithm>
#include <math.h>
#include <cstring>
#include "bag.h"

using namespace::std;

int main(void)
{
    Stack<int> Si(5);
    Stack<float> Sf(6);

    Si.Push(1);
    Si.Push(2);
    Si.Push(3);
    Si.Push(4);
    Si.Push(5);
    cout << "Integer stack has " << Si.Element() << " elements" << endl;
    Si.print_stack();

    Sf.Push(1.1);
    Sf.Push(2.2);
    Sf.Push(3.3);
    Sf.Push(4.4);
    Sf.Push(5.5);
    cout << "Float stack has " << Sf.Element() << " elements" << endl;
    Sf.print_stack();

    Si.Pop();
    Si.Pop();
    cout << "After pop two elements, Integer stack has " << Si.Element() << " elements" << endl;
    cout << "They are: ";
    Si.print_stack();

    Sf.Pop();
    Sf.Pop();
    Sf.Pop();
    cout << "After pop three elements, float stack has " << Sf.Element() << " elements" << endl;
    cout << "They are: ";
    Sf.print_stack();

    cout << "Size (capacity) of integer stack: " << Si.Size() << endl;
    cout << "Size (capacity) of float stack: " << Sf.Size() << endl;

    return 0;
}