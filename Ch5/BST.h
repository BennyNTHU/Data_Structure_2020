//EECS2040 Data Structure Hw #4 (Chapter 5 of textbook)
//due date 5/30/2021
//106061218, Cheng-En Lee
//Part 2, problem 3

#ifndef BST
#define BST

#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include "binarytree.h"

using namespace std;

template <class K, class E> class Dictionary;
template <class K, class E> class BST;

template <class K, class E>
struct pair {
    K first; 
    E second;
};

Pair<K, E>* RankGet(int r);
void Split(const K& k, BST<K, E>& small, pair<K, E>*& mid, BST<K, E>& big);


template <class K, class E>
class Dictionary
{
   public:    
      virtual bool IsEmptay() const = 0;  // return true if dictionary is empty
      virtual pair<K,E>* Get(const K&) const = 0;  // return pointer to the pair w. specified key
      virtual void Insert(const Pair <K, E>&) = 0;   // insert the given pair; if key ia a duplicate, update associate element
      virtual void Delete(const K&) = 0;  // delete pair w. specified key      
};

template<class K, class E>
class BST: public Dictionary, public BinaryTree
{
   private:


   public:    
      virtual bool IsEmptay() const = 0;
      virtual pair<K,E>* Get(const K&) const = 0;
      virtual void Insert(const Pair <K, E>&) = 0;
      virtual void Delete(const K&) = 0;
};

template <class K, class E>
pair<K, E>* BST<K, E> :: Get(const K& k)
{// Driver
    return Get(root, k);
}

template <class K, class E>
pair<K, E>* BST<K, E> :: Get(TreeNode <pair <K, E> >* p, 
                              const K& k)
{// Workhorse
   if (!p) return 0; //empty
   if (k < p->data.first) return Get(p->leftChild, k);
   if (k > p->data.first) return Get(p->rightChild, k);
   return &p->data;
}


template <class K, class E> 
pair<K, E>* BST<K, E>::Get(const K& k)
{ 
   Let currentNode be a pointer point to the root node;
   while (currentNode is not zero) {
       if (k < the key field pointed by currentNode)
          Let currentNode point to the left subtree;
       else if (k > the key field pointed by currentNode)
          Let currentNode point to the right subtree;
       else 
          return the address of the data field pointed by 
          currentNode;
   }
   // no matching pair
   return 0;
}


template <class K, class E> 
pair<K, E>* BST<K, E>::Get(const K& k)
{ 
   TreeNode < pair<K, E> > * currentNode = root;

   while (currentNode) {
       if (k < currentNode->data.first)
          currentNode = currentNode->leftChild;
       else if (k > currentNode->data.first)
          currentNode = currentNode->rightChild;
       else 
          return & currentNode->data;
   } 
   // no matching pair
   return 0;
}


template <class K, class E> 
pair<K, E>* BST<K, E>::RankGet(int r) //search by rank
{ //search the BST for the rth smallest pair
   TreeNode < pair<K, E> > * currentNode = root;
   while (currentNode) {
       if (r < currentNode -> leftSize)
          currentNode = currentNode -> leftChild;
       else if (r > currentNode -> leftSize)
       {   
          r -= currentNode -> leftSize;
          currentNode = currentNode -> rightChild;
       }
       else return & currentNode -> data;
   }
   return 0;
}


template <class K, class E> 
void BST<K, E > :: Insert(const pair<K, E >& thePair)
{  // insert thePair into the BST
   // search for thePair.first，pp parent of p
   TreeNode < pair<K, E> > *p = root, *pp = 0;
   while (p) {
      pp = p;
      if (thePair.first < p->data.first) p = p->leftChild;
      else if(thePair.first > p->data.first)p = p->rightChild;
      else // duplicate, update associated element
          { p->data.second = thepair.second; return;}
   }
   // perform insertion
   p = new TreeNode< pair<K, E> > (thePair);
   if (root) // tree is nonempty
      if (thePair.first < pp->data.first) pp->leftChild = p;
      else pp->rightChild = p
   else root = p;
}


template <class K, class E> 
void BST<K, E>::Split(const K& k, BST<K, E>& small, pair<K, E>*& mid, BST<K, E>& big)
{ // Split the BST with respect to key k
    if (!root) {small.root = big.root = 0; return;} // empty tree
    // create temporary header nodes for small and big
    TreeNode<pair<K, E> > *sHead = new TreeNode<pair<K, E> >,
                          *s = sHead,
                          *bHead = new TreeNode<pair<K, E> >,
                          *b = bHead,
                          *currentNode = root;
    while (currentNode)
        if (k < currentNode->data.first){ // case 1
           b->leftChild = currentNode;
           b = currentNode; currentNode = currentNode->leftChild;
        }
        else if (k > currentNode->data.first) { // case 2
           s->rightChild = currentNode;
           s = currentNode; currentNode = currentNode->rightChild;
        }
        
        else { // case 3
           s->rightChild = currentNode->leftChild;
           b->leftChild = currentNode->rightChild;
           small.root = sHead->rightChild; delete sHead;
           big.root = bHead->leftChild; delete bHead;
           mid = new pair<K, E>(currentNode->data.first, 
                                currentNode->data.second);
           delete currentNode;
           return;
        }
    // no pair with key k
    s->rightChild = b->leftChild = 0;
    small.root = sHead->rightChild; delete sHead;
    big.root = bHead->leftChild; delete bHead;
    mid = 0;
    return;
}

#endif