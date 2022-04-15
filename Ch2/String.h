//EECS2040 Data Structure Hw #1 (Chapter 1, 2 of textbook) 
//due date 4/8/2021 by SNo, 
//106061218, Cheng-En Lee
//Part 2, problem 3

#ifndef STRING
#define STRING
#include <iostream>
#include <math.h>
#include <cstring>
using namespace std;

class String
{
    private:
        int length; // length of the string
        char* str;  // the string
        int* f;     // failure function

    public:
        String(char *init, int m);    // constructor using input string init of length m
        String(const String &s);      // constructor using another string
        ~String();                    // destructor
    
        String Concat(String t);      // concatenation with another string t
        String Substr(int i, int j);  // generate a substring from index i length j
        String Delete(int start, int len);  // delete len characters from index start
        String CharDelete (char c);         // delete a specific character in the string

        void FailureFunction();     // evaluate the failor function and store in f
        char* getString();          // get the string
        int* getf();                // get failure function
        int Length();               // get the number of characters of *this
        int FastFind(String pat);   // Return an index i such that pat matches the substring
                                    // of the object begins at position i. Return -1 if pat
                                    // is empty or not a substring of the object
        
        friend bool operator==(String t1, String t2);   // equality test
        friend bool operator!(String t);                // empty test
        String & operator=(const String &);             // overload assignment
};

bool operator==(String t1, String t2);    //equality test
bool operator!(String t);                 // empty test, return true while string is empty, otherwise false

#endif