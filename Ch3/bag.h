//EECS2040 Data Structure Hw #2 (Chapter 3 of textbook)
//due date 4/17/2021
//106061218, Cheng-En Lee
//Part 2, problem 2

#ifndef BAG
#define BAG

#include <iostream>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;

template <class T>
class Bag
{ 
    protected:
        T* arr;
        int top;
        int capacity;

    public:
        Bag (int c);
        virtual int Size() const;   // return capacity
        virtual bool IsEmpty() const;
        virtual int Element() const;    // return number of elements
        virtual void Push(const T& x);
        virtual void Pop();
};

template <class T>
class Stack: public Bag<T>
{
    public:
        Stack (int c);
        ~Stack();
        T& Top() const;
        void print_stack();
        T* get_stack();
};

template <class T>
void ChangeSize1D (T*&, const int, const int);

template <class T>
Bag<T>::Bag(int c)
{
    if (c < 1)
        throw "Bag capacity must be > 0";
    this->arr = new T[c];
    this->top = -1; // indicate empty stack
    this->capacity = c;
}

template <class T>
Stack<T>::Stack(int c):Bag<T>(c)
{
    if (c < 1)
        throw "Stack capacity must be > 0";
    this->arr = new T[c];
    this->top = -1; // indicate empty stack
    this->capacity = c;
}

template <class T>
Stack<T>::~Stack()
{ 
    delete(this->arr);
}

template <class T>
inline T& Stack<T>:: Top() const
{
    if (*this.IsEmpty()) 
        throw "Stack is empty";
    return *this.arr[*this.top];
}

template <class T>
int Bag<T>::Size() const
{
    return capacity;
}

template <class T>
inline bool Bag<T>::IsEmpty() const
{   
    return top == -1;
}

template <class T>
int Bag<T>::Element() const
{
    return top+1;
}

template <class T>
void Bag<T>::Push(const T& x) // add x to stack
{
    if (top == capacity - 1) 
    {
        ChangeSize1D(arr, capacity, 2 * capacity);	
        capacity *= 2;	
    }
    arr[++top] = x;
}

template <class T>
void Bag<T>::Pop() 
{
    if (IsEmpty()) 
        throw "Bag is empty, cannot delete";	
    int deletePos = top/2;
    arr[top--].~T(); // destructor for T
}

template <class T>
void ChangeSize1D (T*& a, const int oldSize, const int newSize)
{
	if (newSize < 0) 
        throw "New length must be >=0";
	
	T* temp = new T [newSize];    // new array
	int number = min(oldSize, newSize);     // number to copy
	copy (a, a+number, temp);
	delete [] a;      // deallocate old memory
	a = temp;
}

template <class T>
inline T* Stack<T>::get_stack()
{
    return this->arr;
}


template <class T>
void Stack<T>::print_stack()
{
    T* q = this->get_stack();
    cout << "The stack has: ";
    for (int i=0; i<=this->top; i++)
        cout << q[i] << " , ";
    cout << endl;
}

#endif