//EECS2040 Data Structure Hw #3 (Chapter 4 of textbook)
//due date 5/13/2021
//106061218, Cheng-En Lee
//Part 2, problem 3

#ifndef MAT
#define MAT

#include <iostream>
#include <algorithm>
#include <math.h>
#include <cstring>
using namespace std;

struct Triple {
    int row, col, value;
};

class Matrix; // 前向宣告
class MatrixNode;

class MatrixNode 
{
    friend class Matrix;
    
    private:
        MatrixNode *down , *right;
        bool head;
        union { // 沒有名字的union
            MatrixNode *next;
            Triple triple;
        };
        MatrixNode(bool, Triple*); // 建構子

    public:
        friend istream& operator>>(istream&, Matrix&); // 為了能夠讀進矩陣
}

MatrixNode::MatrixNode(bool b, Triple *t)  // 建構子
{
    head = b;
    if (b)   // 列/行的標頭節點
    {
        right = down = this;
    }
    else triple = *t; // 標頭節點串列的元素節點或標頭節點
}

class Matrix
{
    private:
        MatrixNode *headnode;
    
    public:
        Matrix(int row, int col);
        Matrix(const Matrix &M);
        ~Matrix(); // 解構子
        Matrix operator+(const Matrix& b) const;
        Matrix operator*(const Matrix& b) const;
        Matrix Transpose();
        friend istream& operator >> (istream& is, Matrix& matrix);
        friend ostream& operator << (ostream& out, const Matrix& M);   // overload <<
};

istream& operator >> (istream& in, Matrix& M);
ostream& operator << (ostream& out, const Matrix& M);

Matrix::Matrix(int row, int col)
{

}


Matrix::~Matrix()
{
    if (!headnode) 
        return; // no nodes to delete
    MatrixNode *x = headnode->right;

    headnode->right = av; 
    av = headnode; // return headnode

    while (x != headnode)   // return nodes by rows
    { 
        MatrixNode *y = x->right; 
        x->right = av; 
        av = y;
        x = x->next; // next row
    }
    headnode = 0;
}


istream& operator>>(istream& is, Matrix& matrix)    // Read in a maxtix and set up its linked representation
{
    Triple s;
    is >> s.row >> s.col >> s.value; // matrix dimensions
    int p = max(s.row, s.col);  // set up header node for list of  header nodes
    matrix.headnode = new MatrixNode(false, &s);
    if (p == 0) 
    { 
        matrix.headnode->right = matrix.headnode; 
        return is;  // for supporting "cin >> mi >> mj;"
    }
    
    MatrixNode **head = new MatrixNode* [p];    // at least one row or column
    for (int i = 0; i < p; i++)
        head[i] = new MatrixNode(true, 0);

    int currentRow = 0;
    int MatrixNode *last = head[0]; // last node in current row
    for (i = 0; i < s.value; i++)   // input triples
    {
        Triple t;
        is >> t.row >> t.col >> t.value;
        if (t.row > currentRow) // end of current row 
        { 
            last->right = head[currentRow]; // close current row
            currentRow = t.row;
            last = head[currentRow];
        }

        last = last->right = new MatrixNode(false, &t); // link new node into row list
        head[t.col]->next = head[t.col]->next->down = last; // link into column list
    } 
    last->right = head[currentRow]; // close last row
    for (i = 0; i < s.col; i++) 
        head[i]->next->down = head[i] // close all column lists
   
    for (i = 0; i < p; i++) // link the header nodes together
        head[i]->next = head[i + 1];
    head[p-1]->next = matrix.headnode;
    matrix.headnode->right = head[0];

    delete [] head;
    return is;
}

ostream& operator << (ostream& out, const Matrix& M);
{
    out << "(row,col,value)" << endl;   
	for (int i=0; i<b.terms; i++)   // print the (row, col, value) triple
        out << '(' << b.smArray[i].get_row() << ',' <<  b.smArray[i].get_col()
            << ',' << b.smArray[i].get_value() << ')' << endl;
    return out;
}



#endif
