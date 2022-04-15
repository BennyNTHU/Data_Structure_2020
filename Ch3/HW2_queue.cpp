//EECS2040 Data Structure Hw #2 (Chapter 3 of textbook)
//due date 4/17/2021
//106061218, Cheng-En Lee
//Part 2, problem 1

#include <iostream>
#include <algorithm>
#include <math.h>
#include <cstring>
#include "queue.h"

using namespace::std;

int main(void)
{
    Queue<int> A(10);
    Queue<int> B(5);

    cout << "capacity of A=" << A.get_capacity() << endl;
    cout << "capacity of B=" << B.get_capacity() << endl;
    
    A.Push(1);
    A.Push(2);
    A.Push(3);
    A.Push(4);
    A.Push(5);
    
    cout << "A.IsEmpty()=" << A.IsEmpty() << endl;
    cout << "B.IsEmpty()=" << B.IsEmpty() << endl;

    B.Push(87);
    B.Push(63);
    B.Push(48763);

    A.print_queue();
    B.print_queue();

    cout << "size of A=" << A.get_size() << endl;
    cout << "size of B=" << B.get_size() << endl;
    
    A.Pop();
    cout << "pop an element of A: " << endl;
    A.print_queue();

    cout << "merge A and B: " << endl;
    Queue<int> C = merge(A,B);
    C.print_queue();

    return 0;
}