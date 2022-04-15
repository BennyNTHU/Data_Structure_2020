//EECS2040 Data Structure Hw #4 (Chapter 5 of textbook)
//due date 5/30/2021
//106061218, Cheng-En Lee
//Part 2, problem 1

#ifndef BINARYTREE
#define BINARYTREE

#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <stack>
#include <queue>
using namespace std;

template<class T> class BinaryTree;
template <class T> class Tree;

template <class T>
class TreeNode 
{
    friend class BinaryTree<T>;

    private:
        T data;
        TreeNode<T> *leftChild;
        TreeNode<T> *rightChild;

    public:
        TreeNode()
        {
            leftChild = nullptr;
            rightChild = nullptr;
        }
        TreeNode(const T& e, TreeNode<T>* ptr_left, TreeNode<T>* ptr_right)
        {
            data = e; 
            leftChild = ptr_left;
            rightChild = ptr_right; 
        }
        TreeNode(const T& e)
        {
            data = e;
            leftChild = nullptr;
            rightChild = nullptr;
        }
        T getdata()
        {
            return data;
        }
        TreeNode<T>* get_left_child()
        {
            return this->leftChild;
        }
        TreeNode<T>* get_right_child()
        {
            return this->rightChild;
        }
        TreeNode<T>* setNode(T in)
        {
            return this->data = in;
        }
        TreeNode<T>* set_left_child(TreeNode *in)
        {
            return this->left_child = in;
        }
        TreeNode<T>* set_right_child(TreeNode *in)
        {
            return this->right_child = in;
        }
};

template<class T>
class BinaryTree
{
    private:
	    TreeNode<T> *root;

    public:
        // constructor & destructor
        BinaryTree(); // constructor for an empty binary tree
        BinaryTree(BinaryTree<T>& bt1, T& item, BinaryTree<T>& bt2);    // copy constructor 1
        BinaryTree(const BinaryTree<T>& bt);    // copy constructor 2
        ~BinaryTree(); // destruvtor
        void delete_tree(TreeNode<T>* node); // delete a subtree
           
        // return properties
        T RootData();  // return the data in the root node of *this
        TreeNode<T>* get_root();
        void set_root(TreeNode<T>* node);
	    BinaryTree<T> LeftSubtree(); // return the left subtree
        BinaryTree<T> RightSubtree();// return the right subtree
        bool IsEmpty(); // return true iff the binary tree is empty

        // traversals
        void Inorder();
        void Inorder(TreeNode<T> *p);
        void Visit(TreeNode<T> *p);
        void Preorder();
        void Preorder(TreeNode<T> *t);
        void Postorder();
        void Postorder(TreeNode<T> *t);
        void LevelOrder();
        void NonrecInorder();
        void NoStackInorder();

        // operation overload
        bool operator==(const BinaryTree& bt);
        bool root_equal(TreeNode<T>* root1, TreeNode<T>* root2);
        TreeNode<T>* copy_node(TreeNode<T>* in);   // I don't know how to overload = so I use this method
};

template <class T>
BinaryTree<T>::BinaryTree()
{
    root = nullptr;
}

template <class T>
BinaryTree<T>::BinaryTree(BinaryTree<T>& bt1, T& item, BinaryTree<T>& bt2)  // Copy constructor 1
{
    root = item;
    root->set_left_child(bt1.get_root());
    root->set_right_child(bt2.get_root());
}

template <class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& bt)  // Copy constructor 2
{
    root = copy_node(bt.root);
}

template <class T>
BinaryTree<T>::~BinaryTree()
{
    delete_tree(root);
}

template <class T>
void BinaryTree<T>::delete_tree(TreeNode<T>* node)
{
    if(node != nullptr)
    {
        delete_tree(node->leftChild);
        delete_tree(node->rightChild);
        delete node;
    }
}
template <class T>
T BinaryTree<T>::RootData()
{
    return root->getdata();
}

template <class T>
TreeNode<T>* BinaryTree<T>::get_root()
{
    return this->root;
}

template <class T>
void BinaryTree<T>::set_root(TreeNode<T>* node)
{
    root = node;
}

template <class T>
BinaryTree<T> BinaryTree<T>::LeftSubtree()
{
	BinaryTree<T> left_subtree;
	left_subtree.root = copy_node(root->leftChild);
	return left_subtree;
};

template <class T>
BinaryTree<T> BinaryTree<T>::RightSubtree()
{
    BinaryTree<T> right_subtree;
	right_subtree.root = copy_node(root->rightChild);
	return right_subtree;
};

template <class T>
bool BinaryTree<T>::IsEmpty()
{
    return root==nullptr;
}

template <class T>
void BinaryTree<T>::Inorder()
{
    Inorder(root);   // Traverse inorderly
}


template <class T>
void BinaryTree<T>::Inorder(TreeNode<T> *p)
{
    if (p != nullptr) 
    {
        Inorder(p->leftChild);  // L
        Visit(p);               // visit
        Inorder(p->rightChild); // R
    }
}

template <class T>
void BinaryTree<T>::Visit(TreeNode<T> *p)
{
    cout << p->data;  
}

template <class T>
void BinaryTree<T>::Preorder()
{ 
    Preorder(root); //Traverse preorderly
}

template <class T>
void BinaryTree<T>::Preorder(TreeNode<T> *t)
{
    if (t != NULL)
    {
        Visit(t); 
        Preorder(t->leftChild);   
        Preorder(t->rightChild);
    }
}

template <class T>
void BinaryTree<T>::Postorder()
{
    Postorder(root);    //Traverse postorderly
}


template <class T>
void BinaryTree<T>::Postorder(TreeNode<T>* t)
{
    if (t != nullptr)
    {
        Postorder(t->leftChild);   
        Postorder(t->rightChild);
        Visit(t);  
    }
}

template <class T>
void BinaryTree<T>::LevelOrder()
{
    queue <TreeNode<T>*> q;
    TreeNode<T> *currentNode = root;
    while (currentNode) 
    {
        Visit(currentNode);
        if (currentNode->leftChild)
            q.push(currentNode->leftChild);

        if (currentNode->rightChild) 
            q.push(currentNode->rightChild);

        if (q.empty()) 
            return;
        currentNode = q.front();
        q.pop();
    }
}

template <class T>
void BinaryTree<T>::NonrecInorder() // nonrecursive inorder traversal
{
    stack <TreeNode<T>*> s;  
    TreeNode<T> *currentNode = root;

    while(1) 
    {
        while (currentNode) 
        { 
            s.push(currentNode);
            currentNode = currentNode->leftChild;
        }
        if (s.empty()) 
            return;
        currentNode = s.top();
        s.pop(); 
        Visit(currentNode);
        currentNode = currentNode->rightChild;
    }
}

template <class T>
void BinaryTree<T>::NoStackInorder()
{
	if (!root) 
        return; // empty binary tree

	TreeNode<T> *top = 0, *lastRight =0, *p, *q, *r, *r1;
	p = q = root;
	
    while(1) 
    {
	    while(1) 
        {
	        if ((!p->leftChild) && (!p->rightChild)) //樹葉節點
            { 
                Visit(p);
                break;
            }
            if (!p->leftChild)   
            { 
                Visit(p);   // 拜訪p並移至p->rightChild
                r = p->rightChild; p->rightChild = q;
                q = p; p = r;
            }
            else    // 移至p->leftChild
            { 
                r = p->leftChild; 
                p->leftChild = q;
                q = p; 
                p = r;
            }
        }
    
        TreeNode<T> *av = p;    // p是一個葉節點，向上移至右子樹還沒被檢查的節點

        while(1) 
        {
            if (p == root) 
                return;
            if (!q->leftChild)   // q是透過rightChild鏈結的
            { 
                r = q->rightChild; 
                q->rightChild = p;
                p = q; 
                q = r;
            }
            else if (!q->rightChild) // q是透過leftChild鏈結的
            { 
                r = q->leftChild; 
                q->leftChild = p;
                p = q; 
                q = r; 
                Visit(p);
            }
            else // 檢查p是否為q的rightChild
            { 
                if (q == lastRight) 
                {
                    r = top; 
                    lastRight = r->leftChild;
                    top = r->rightChild; // 彈出堆疊
                    r->leftChild = r->rightChild = 0;
                    r = q->rightChild; 
                    q->rightChild = p;
                    p = q; 
                    q = r;
                }
                else 
                { // p是q的leftChild
                    Visit(q);
                    av->leftChild = lastRight; 
                    av->rightChild = top;
                    top = av; 
                    lastRight = q;
                    r = q->leftChild; 
                    q->leftChild = p;
                    r1 = q->rightChild; 
                    q->rightChild = r;
                    p = r1;
                    break;
                }
            }
        }
    }
}

template <class T>
bool BinaryTree<T>::root_equal(TreeNode<T>* root1, TreeNode<T>* root2)
{
    if ((root1==nullptr) && (root2==nullptr))
        return true;
    else if ((root1 != nullptr) && (root2 != nullptr))
        return (root1->data == root2->data) &&
                root_equal(root1->leftChild, root2->leftChild) &&
                root_equal(root1->rightChild, root2->rightChild);
    else
        return false;
}

template <class T>
bool BinaryTree<T>::operator==(const BinaryTree& bt)
{
    return root_equal(root, bt.root);
}

template <class T>
TreeNode<T>* BinaryTree<T>::copy_node(TreeNode<T>* in)
{
    if (in==nullptr)
        return nullptr;
    return new TreeNode<T>(in->data, copy_node(in->leftChild), copy_node(in->rightChild));
}

#endif