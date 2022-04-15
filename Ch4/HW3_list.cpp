//EECS2040 Data Structure Hw #3 (Chapter 4 of textbook)
//due date 5/14/2021
//106061218, Cheng-En Lee
//Part 2, problem 1

#include <iostream>
#include <algorithm>
#include "list.h"
using namespace std;

int main(void)
{
    List<int> A;
    List<int> B;

    /* insertion */
    for (int i=1; i<=5; i++)
    {
        A.InsertBack(i);
        B.InsertBack(i);
    }
    cout << "insert 1, 2, 3, 4, 5: " << A;

    A.InsertFront(0);
    cout << "insert 0 at front: " << A;
    A.Insert(3,6);
    cout << "insert 6 at position 3: " << A;

    A.DeleteFront();
    cout << "delete at front: " << A;
    A.DeleteBack();
    cout << "delete at back: " << A;
    A.Delete(2);
    cout << "delete at position 2: " << A;

    A.Concatenate(B);
    cout << "concatenate A with B=1,2,3,4,5:" << A;
    A.Reverse();
    cout << "reverse A:" << A;

    return 0;
}
