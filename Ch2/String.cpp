//EECS2040 Data Structure Hw #1 (Chapter 1, 2 of textbook) 
//due date 4/8/2021 by SNo, 
//106061218, Cheng-En Lee
//Part 2, problem 3

#include <iostream>
#include <algorithm>
#include <cstring>
#include "String.h"
using namespace std;

String::String(char *init, int m)   // constructor using input string init of length m
{
    length = m;
    str = (char *)calloc(length, sizeof(char));
    f = (int *)calloc(length, sizeof(int));
    for (int i=0; i<length; i++)
        str[i] = init[i];
    FailureFunction();  // evaluate the failor function and store in f
}

String::String(const String &s) // constructor using another string
{
    length = s.length;  // copy all attributes
    str = (char *)calloc(length, sizeof(char));
    for (int i=0; i<length; i++)
        str[i] = s.str[i];
    f = s.f;
}

String::~String()   // destructor
{
    free(str);
    free(f);
}

String String::Concat(String t) // concatenation with another string t
{
    int new_length = length+t.Length(); // new length
    char A[new_length] = {0};           // the concated string
    
    for (int i=0; i<length; i++)        // concate process
        A[i] = str[i];
    for (int i=length; i<new_length; i++)
        A[i] = t.getString()[i-length];

    String concat_str(A ,new_length);   // construct the concated string
    return concat_str;
}

String String::Substr(int i, int j) // generate a substring from index i length j
{
    if (i+j-1>length-1)
        throw "out of range!!";
    
    char substring[j] = {0};
    for (int k=0; k<j; k++)
        substring[k] = str[i+k];

    String Sub(substring, j);
    return Sub;
}

String String::Delete(int start, int len)   // delete len characters from index start
{
    if (start>length-1 || len > length)
        throw "out of range!!";
    
    int del_length = length - len;          // the length of the deleted string
    char del_str[del_length] = {0};         // the deleted string

    for (int i=0; i<start; i++)             // the characters before start
        del_str[i] = str[i];
    for (int i=start+len; i<length; i++)    // the characters from start+len to the end of string
        del_str[i-len] = str[i];
    
    String D(del_str, del_length);          // construct the return string
    return D;
}

String String::CharDelete(char c)   // delete a specific character in the string
{   
    char* del_str = str;        // the new string
    char del_length = length;   // the length of the new string, default = initial length

    for (int i=1; i<length; i++)
        if (str[i]==c)          // the specific character is found
        {
            for (int j=i; j<length; j++)
                del_str[j] = str[j+1];  // omit that character and store the next character to del_str
            del_length--;               // update length
        }

    String CD(del_str, del_length);     // construct the return string
    return CD;
}

void String::FailureFunction()  // evaluate the failor function and store in f
{
    int lengthP = Length();
    f[0] = -1;
    for (int j = 1; j < lengthP; j++) 
    {
        int i = f[j-1];
        while ((str[j] != str[i+1]) && (i >= 0)) 
            i = f[i];
        if (str[j] == str[i+1]) 
            f[j] = i+1;
        else 
            f[j] = -1;
    }
}

char* String::getString()   // get the string
{
    return str;
}

int* String::getf()    // get failure function
{
    return f;
}

int String::Length()   // get the number of characters of *this
{
    return length;
}

int String::FastFind(String pat) 
{
    int posP = 0, posS = 0;
    int lengthP = pat.Length(), lengthS = Length();
    while((posP < lengthP) && (posS < lengthS))
    {
        if (pat.str[posP] == str[posS]) 
        {  
            posP++; 
            posS++;    
        }
        else
        {
            if (posP == 0) 
                posS++;
            else 
                posP = pat.f[posP -1] + 1;
        }
    }
    if (posP < lengthP) 
        return -1;
    else // Textbook stops pattern matching once a match is found
        return posS-lengthP;
}

bool operator==(String t1, String t2)   // equality test
{
    return strcmp(t1.getString(), t2.getString()) == 0;
}

bool operator!(String t)    // empty test, return true while string is empty, otherwise false
{
    if (t.Length()==0)
        return true;
    else
        return false;
}

String & String::operator=(const String &t) // overload assignment
{
    str = t.str;    // copy every attributes
    length = t.length;
    f = t.f;

    return *this;
}
