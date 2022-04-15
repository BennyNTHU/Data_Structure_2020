//EECS2040 Data Structure Hw #3 (Chapter 4 of textbook)
//due date 5/13/2021
//106061218, Cheng-En Lee
//Part 2, problem 1

#ifndef LIST
#define LIST

#include <iostream>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;

template <class T> class List;
template <class T> class Node;
template <class T> class ChainIterator;

template <class T>
class Node
{
    friend class List<T>;
    friend class ChainIterator<T>;

    private:  
        T data;
        Node* link;

    public:
        Node()
        {
            link = nullptr;
        }
        Node(const T& e, Node<T> * ptr)
        {
            data = e; 
            link = ptr;
        }
        Node(const T& e)
        {
            data = e; 
            link = nullptr;
        }
        T getNode()
        {
            return data;
        }
        Node<T>* getLink()
        {
            return this->link;
        }
        Node<T>* setNode(T in)
        {
            return this->data = in;
        }
        Node<T>* setLink(Node *in)
        {
            return this->link = in;
        }
};

template <class T>
class List
{
    friend class ChainIterator<T>;

    private:
        Node<T>* first;

    public:
        /* constructor and destructors */
        List();  // constructor
        ~List(); // destructor
        //Note: using default destructor also WORKS

        /* insertion */
        void InsertFront(const T& e); // insert at the front of the list
        void InsertBack(const T& e);    // insert at the end of the list
        void Insert(int i, T e); // insert as the ith element

        /* deletion */
        void DeleteFront();  // delete at the front
        void DeleteBack();   // delete at the end
        void Delete(int i);  // delete the ith element

        /* return elements */
        Node<T>* Front();    // return the first elements of the list
        Node<T>* Back();     // return the last elements of the list
        Node<T>* Get(int i); // returns the ith element in the list

        /* Other functions */
        void Concatenate(List<T>& b);   // concatenate two list
        void Reverse(); // reverse the list

        /* overloading */
        friend ostream& operator << (ostream& out, const List<T> &b)   // overload <<
        {
            if (b.first == nullptr)
                throw "The list is empty";

            for (List<T>::ChainIterator i=b.begin(); i!=b.end(); i++)
                out << *i << "->";
            
            std::cout << "null" << endl;
            return out;
        }

        /* iterator */
        class ChainIterator
        {
            private:  
                Node<T>* current;

            public:
                //Constructor
                ChainIterator(Node<T>* startNode = 0) 
                {
                    current = startNode;
                }
  
                //Dereferencing operators
                T& operator *() const 
                {
                    return current -> data;
                }
                T* operator ->() const 
                {
                    return &current -> data;
                }
  
                //Increment
                ChainIterator& operator ++()    //preincrement
                {
                    current = current ->link; 
                    return *this;
                }
                ChainIterator operator ++(int) //postincrement
                {
                    ChainIterator copy = *this;
                    ++(*this); 
                    return copy;
                }
  
                //Equality test
                bool operator!=(const ChainIterator r)
                {
                    return current != r.current;
                }
                bool operator==(const ChainIterator r)
                {
                    return current == r.current;
                }
            };
            
        //More functions
        ChainIterator begin() const
        {
            return ChainIterator(first);
        }
        ChainIterator end() const
        {
            return ChainIterator(0);
        }
};

template <class T>
List<T>::List()
{
    first = nullptr;
}

template <class T>
List<T>::~List()
{
    Node<T>* deleteNode = first;
    Node<T>* ptr = deleteNode->link;

    while (ptr != nullptr) 
    {
        delete deleteNode;
        Node<T>* deleteNode = ptr;
        ptr = ptr->link;
    }
}

template <class T>
void List<T>::InsertFront(const T& e)
{
    if (first==nullptr)
        first = new Node<T>(e, nullptr);
    else
    {
        Node<T> *newNode = new Node<T>(e, first);
        first = newNode;
    }
}

template <class T>
void List<T>::InsertBack(const T& e)
{
    if (first == nullptr) 
    {                      
        first = new Node<T>(e);    // 若list沒有node, 令newNode為first
        return;
    }
    else
    {
        Node<T> *last = first;
        while (last->link != nullptr)  // Traversal
        {           
            last = last->link;
        }
        Node<T> *newNode = new Node<T>(e, nullptr);   // 配置新的記憶體
        last->link = newNode;    // 將newNode接在list的尾巴
    }
}

template <class T>
void List<T>::Insert(int i, T e)
{
    Node<T> *newNode = new Node<T>(e);   // 配置新的記憶體
    Node<T> *current = first;
    int j = 0;

    while (j < i-1)  // Traversal
    {           
        current = current->link;
        if (current->link == NULL)
        {
            throw "the length of list is < i !";
        }
        j++;
    }

    newNode->link = current->link;
    current->link = newNode;    // 將newNode接在list的尾巴
}

template <class T>
void List<T>::DeleteFront()  // delete at the front
{
    Node<T>* deleteNode = first;
    first = first->link;
    delete deleteNode;
}

template <class T>
void List<T>::DeleteBack()   // delete at the end
{
    Node<T> *current = first;

    while (current->link->link != NULL)  // Traversal
    {           
        current = current->link;
    }
    Node<T> *deleteNode = current->link;
    delete deleteNode;
    current->link = NULL;
}

template <class T>
void List<T>::Delete(int i)  // delete the ith element
{
   if (first == NULL) 
        throw "Cannot delete from empty chain";

    Node<T>* deleteNode;
    if (i == 0)  // remove first node from chain
    {
        deleteNode = first;
        first = first->link;
    }
    else    // use p to get to beforeNode
    {  
        Node<T>* p = first;
        for (int j = 0; j < i - 1; j++)
        {
            if (p == 0) 
                throw "Delete element does not exist";
            p = p->link;
        }
        deleteNode = p->link;
        p->link = p->link->link; 
    }
    delete deleteNode;
}

template <class T>
Node<T>* List<T>::Front()  // return the first elements of the list
{
    return first;
}

template <class T>
Node<T>* List<T>::Back()   // return the last elements of the list
{
    Node<T> *current = first;
    while (current->link != 0)  // Traversal
    {           
        current = current->link;
    }
    return current;
}

template <class T>
Node<T>* List<T>::Get(int i) // returns the ith element in the list
{
    Node<T> *current = first;
    int j = 0;

    while (j < i-1)  // Traversal
    {           
        current = current->link;
        if (current->link == NULL)
        {
            throw "the length of list is < i !";
        }
        j++;
    }
    return current;
}

template <class T>
void List<T>::Concatenate(List<T>& b)   // concatenate two list
{
    Node<T> *current = first;
    while (current->link != 0)  // Traversal
    {           
        current = current->link;
    }
    current->link = b.first;
}

template <class T>
void List<T>::Reverse()
{
    Node<T> *curr = first;
    Node<T> *prev = 0;  
    Node<T> *r = 0;
    
    while (curr != NULL) 
    {
        r = prev;          // r trails prev 
        prev = curr;       // prev trails curr
        curr = curr->link; // curr moves to the link
        prev->link = r;    // link prev to r
    }
    first = prev;
}

#endif