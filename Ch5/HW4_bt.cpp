//EECS2040 Data Structure Hw #4 (Chapter 5 of textbook)
//due date 5/30/2021
//106061218, Cheng-En Lee
//Part 1, problem 1

#include <iostream>
#include <algorithm>
#include <math.h>
#include <cstring>
#include "binarytree.h"

using namespace::std;

int main(void)
{
    BinaryTree<char> T1, T2, T1_left_subtree, T2_left_subtree, T1_right_subtree, T2_right_subtree;

    TreeNode<char> *A1 = new TreeNode<char>('A');
    TreeNode<char> *B1 = new TreeNode<char>('B');
    TreeNode<char> *minus = new TreeNode<char>('-', A1, B1);
    TreeNode<char> *C1 = new TreeNode<char>('C');
    TreeNode<char> *multiply1 = new TreeNode<char>('*', minus, C1);
    TreeNode<char> *D1 = new TreeNode<char>('D');
    TreeNode<char> *multiply2 = new TreeNode<char>('*', multiply1, D1);
    TreeNode<char> *E1 = new TreeNode<char>('E');
    TreeNode<char> *plus = new TreeNode<char>('+', multiply2, E1);
    T1.set_root(plus);

    TreeNode<char> *H = new TreeNode<char>('H');
    TreeNode<char> *J = new TreeNode<char>('J');
    TreeNode<char> *D = new TreeNode<char>('D', H, J);
    TreeNode<char> *E = new TreeNode<char>('E');
    TreeNode<char> *B = new TreeNode<char>('B', D, E);
    TreeNode<char> *F = new TreeNode<char>('F');
    TreeNode<char> *G = new TreeNode<char>('G');
    TreeNode<char> *C = new TreeNode<char>('C', F, G);
    TreeNode<char> *A = new TreeNode<char>('A', B, C);
    T2.set_root(A);
    
    T1_left_subtree = T1.LeftSubtree();
    T1_right_subtree = T1.RightSubtree();
    
    cout << "root data of T1: " << T1.RootData() << endl;
    cout << "root data of T1: " << T1_left_subtree.RootData() << endl;
    cout << "LeftSubtree of T1 (preorder): ";     T1_left_subtree.Preorder();     cout << endl;
    cout << "RightSubtree of T1 (preorder): ";    T1_right_subtree.Preorder();    cout << endl;
    cout << "Is T1 empty? (No: 0, Yes: 1): " << T1.IsEmpty() << endl;

    cout << "inorder traversal of T1: ";                T1.Inorder();           cout << endl;
    cout << "preorder traversal of T1: ";               T1.Preorder();          cout << endl;
    cout << "postorder traversal of T1: ";              T1.Postorder();         cout << endl;
    cout << "levelorder traversal of T1: ";             T1.LevelOrder();        cout << endl;
    cout << "Non recursive inorder traversal of T1: ";  T1.NonrecInorder();     cout << endl;
    cout << "No stack inorder traversal of T1: ";       T1.NoStackInorder();    cout << endl;

    T2_left_subtree = T2.LeftSubtree();
    T2_right_subtree = T2.RightSubtree();

    cout << "root data of T2: " << T2.RootData() << endl;
    cout << "LeftSubtree of T2 (inorder): ";     T2_left_subtree.Inorder();     cout << endl;
    cout << "RightSubtree of T2 (inorder): ";    T2_right_subtree.Inorder();    cout << endl;
    cout << "Is T2 empty? (No: 0, Yes: 1): " << T2.IsEmpty() << endl;

    cout << "inorder traversal of T2: ";                T2.Inorder();           cout << endl;
    cout << "preorder traversal of T2: ";               T2.Preorder();          cout << endl;
    cout << "postorder traversal of T2: ";              T2.Postorder();         cout << endl;
    cout << "levelorder traversal of T2: ";             T2.LevelOrder();        cout << endl;
    cout << "Non recursive inorder traversal of T2: ";  T2.NonrecInorder();     cout << endl;
    cout << "No stack inorder traversal of T2: ";       T2.NoStackInorder();    cout << endl;

    BinaryTree<char> T3(T1);
    cout << "construct T3 by T1 and copy constructor" << endl;
    cout << "inorder traversal of T3: ";                T3.Inorder();           cout << endl;;

    if (T1==T3)
        cout << "T1==T3" << endl;

    return 0;
}
