//EECS2040 Data Structure Hw #3 (Chapter 4 of textbook)
//due date 5/16/2021
//106061218, Cheng-En Lee
//Part 2, problem 2

#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include "node.h"

Node::Node()
{
	this->coef = 0;
	this->exp = 0;
	this->next = nullptr;
}

double Node::GetCoef()
{
	return this->coef;
}

int Node::GetExp()
{
	return this->exp;
}

Node* Node::GetNext()
{
	return this->next;
}

void Node::DeleteNext(Node **node)
{
	if ((*node)->next == (*node))
	{
		(*node)->next = nullptr;
		(*node)->RetNode();
		(*node) = nullptr;
	}
	else
	{
		Node *toDel = (*node)->next;
		(*node)->next = toDel->next;
		toDel->next = nullptr;
		toDel->RetNode();
	}
}

int Node::AvailableNodeCount()
{
	return ChainLength(IdleNodes);
}

int Node::ChainLength(Node *node)
{
	if (node == nullptr)
	{
		return 0;
	}

	int count = 1;
	Node *cur = node->next;

	while (cur != node)
	{
		cur = cur->next;
		count++;
	}

	return count;
}

void Node::InsertEmpty(Node **node)
{
	if (*node == nullptr)
	{
		*node = GetNode();
		(*node)->next = *node;
	}
	else
	{
		Node *second = (*node)->next;
		Node *newNode = GetNode();
		(*node)->next = newNode;
		newNode->next = second;
	}
}

Node* Node::GetNode()
{
	// At start / running out of nodes: create new ones
	if (IdleNodes == nullptr)
	{
		IdleNodes = new Node();
		Node *cur = IdleNodes;
		int NUMNODES = 10;
		for (int i = 1; i <= NUMNODES - 1; i++)
		{
			Node *next = new Node();
			cur->Set(next);
			cur = next;

			if (i == NUMNODES - 1)
			{
				cur->next = IdleNodes;
			}
		}
	}

	// Retrive one node: only one node left
	if (IdleNodes == IdleNodes->next)
	{
		Node *result = IdleNodes;
		result->Set(0, 0, nullptr);
		IdleNodes = nullptr;
		return result;
	}

	// otherwise
	Node *result = IdleNodes->next;
	IdleNodes->next = result->next;
	result->Set(0, 0, nullptr);
	return result;
}

void Node::Set(double coef, int exp) 
{ 
	this->coef = coef; 
	this->exp = exp;
}

void Node::Set(Node* next) 
{ 
	this->next = next;
}

void Node::Set(double coef, int exp, Node* next) 
{ 
	this->coef = coef; 
	this->exp = exp;
	this->next = next;
}

// Cut the first link, making it a simple singly linked list
// Then linearly return these nodes
void Node::RetNode()
{
	Node* cur = this->next;
	this->next = nullptr;

	while (true)
	{
		Node* toDel = cur;

		if (toDel == nullptr)
		{
			break;
		}

		cur = cur->next;
		toDel->Set(0, 0, nullptr);

		// Return the node toDel
		if (IdleNodes == nullptr)
		{
			IdleNodes = toDel;
			IdleNodes->Set(toDel);
		}
		else
		{
			Node *secondIdle = IdleNodes->next;
			IdleNodes->next = toDel;
			toDel->next = secondIdle;
		}
	}
}

Node *Node::IdleNodes = nullptr;