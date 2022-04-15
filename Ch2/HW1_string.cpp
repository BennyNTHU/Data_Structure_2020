//EECS2040 Data Structure Hw #1 (Chapter 1, 2 of textbook) 
//due date 4/8/2021 by SNo, 
//106061218, Cheng-En Lee
//Part 2, problem 3

#include <iostream>
#include <algorithm>
#include <math.h>
#include "String.h"
#include <cstring>
using namespace::std;

int main(void)
{
    // every string used, sufficies of two run
    string smix = "tiger fire cyber fiber diver viber jarjar";
    string smix2 = "tora hi jinzou seni ama shindou kasen";
    string smix3 = smix;
    string sF = "fiber";
    string sempty = "";
    string spattern = "r";

    // convert every string into array of characters
    char mix[smix.length() + 1];
    strcpy(mix, smix.c_str());
    char mix2[smix2.length() + 1];
    strcpy(mix2, smix2.c_str());
    char mix3[smix3.length() + 1];
    strcpy(mix3, smix3.c_str());
    char F[sF.length() + 1];
    strcpy(F, sF.c_str());
    char empty[sempty.length() + 1];
    strcpy(empty, sempty.c_str());
    char pattern[spattern.length() + 1];
    strcpy(pattern, spattern.c_str());

    String MIX(mix, 41);
    cout << MIX.getString() << endl;
    cout << "length of MIX: " << MIX.Length() << endl;
    String SF(F, 5);
    cout << "fiber in MIX found in: " << MIX.FastFind(SF) << endl;

    String MIX2(mix2, 37);
    String MIX3(mix3, 41);
    cout << "MIX==MIX2? " << (MIX==MIX2) << endl;
    cout << "MIX==MIX3? " << (MIX==MIX3) << endl;

    String E(empty, 0);
    cout << "is E empty? " << !(E) << endl;
    cout << "is MIX empty? " << !(MIX) << endl;

    cout << "concat MIX and MIX2: " << MIX.Concat(MIX2).getString() << endl;
    String MIX5(MIX.Substr(3,10));
    cout << "substring of MIX from 3 length 10: " << MIX5.getString() << endl;
    String MIX6 = MIX.Delete(3,10);
    cout << "MIX6 = delete MIX from 3 length 10: " << MIX6.getString() << endl;
    cout << "length of MIX6 = " << MIX6.Length() << endl;
    String MIX7 = MIX.CharDelete('r');
    cout << "delete r from MIX: " << MIX7.getString() << endl;

    return 0;
}
