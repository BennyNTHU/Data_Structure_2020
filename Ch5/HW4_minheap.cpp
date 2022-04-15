//EECS2040 Data Structure Hw #4 (Chapter 5 of textbook)
//due date 5/30/2021
//106061218, Cheng-En Lee
//Part 2, problem 2(b)

#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include "minheap.h"

using namespace std;

int main(void)
{
    MinHeap<int> H(5);

    for (int i=1; i<=5; i++)    // Push 1~5
        H.Push(i);
    
    cout << "insert 1,2,3,4,5" << endl;;
    for (int i=1; i<=H.get_size(); i++)
        cout << H.get_heap()[i] << " ";
    cout << endl;

    cout << "Is the heap empty? (No: 0, Yes: 1): " << H.IsEmpty() << endl;
    cout << "The element with highest priority: " << H.Top() << endl;
    cout << "There are " << H.get_size() << " elements in this heap now" << endl;
    cout << "The capacity of this heap: " << H.get_capacity() << endl;

    H.Pop();
    cout << "Now pop 1 element" << endl;
    cout << "There are " << H.get_size() << " elements in this heap now" << endl;
    for (int i=1; i<=H.get_size(); i++)
        cout << H.get_heap()[i] << " ";
    cout << endl;
    cout << "The element with highest priority: " << H.Top() << endl;
    
    return 0;
}