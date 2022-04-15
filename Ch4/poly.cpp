//EECS2040 Data Structure Hw #3 (Chapter 4 of textbook)
//due date 5/16/2021
//106061218, Cheng-En Lee
//Part 2, problem 2

#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include "node.h"
#include "poly.h"

void Polynomial::trimZero()
{
	if (this->poly == nullptr)
	{
		return;
	}

	// find the first non-zero term. does not affect the desc order property.
	int length = Node::ChainLength(this->poly);

	for (int i = 0; i < length; i++)
	{
		if (abs(this->poly->GetCoef()) > 0.00001)
		{
			break;
		}

		this->poly = this->poly->GetNext();
	}

	if (abs(this->poly->GetCoef()) <= 0.00001)
	{
		this->poly->RetNode();
		this->poly = nullptr;
		return;
	}

	Node *cur = this->poly;
	for (int i = 0; i < length; i++)
	{
		while (abs(cur->GetNext()->GetCoef()) <= 0.00001)
		{
			Node::DeleteNext(&cur);
		}
		cur = cur->GetNext();
	}
}

Polynomial::Polynomial()
{
	this->poly = nullptr;
}

Polynomial::Polynomial (const Polynomial& a)
{
	// Create a chain of terms of the same length with a
	this->poly = nullptr;

	if (a.poly == nullptr)
	{
		return;
	}

	int length = Node::ChainLength(a.poly);
	for (int i = 0; i < length; i++)
	{
		Node::InsertEmpty(&(this->poly));
	}
	
	// Fill in data
	Node *nodeA = a.poly;
	Node *nodeSelf = this->poly;

	do
	{
		nodeSelf->Set(nodeA->GetCoef(), nodeA->GetExp());
		nodeA = nodeA->GetNext();
		nodeSelf = nodeSelf->GetNext();
	} while (nodeSelf != this->poly);
}

Polynomial::~Polynomial()
{
	if (this->poly != nullptr)
	{
		this->poly->RetNode();
	}
}

std::istream& operator>> (std::istream& in, Polynomial& x)
{
	if (x.poly != nullptr)
	{
		x.poly->RetNode();
		x.poly = nullptr;
	}

	int length;
	std::cout << "the length of this polynomial: ";
	in >> length;

	for (int i = 0; i < length; i++)
	{
		Node::InsertEmpty(&x.poly);
	}

	Node *cur = x.poly;
	for (int i = 0; i < length; i++, cur = cur->GetNext())
	{
		double coef;
		int exp;
		std::cout << "enter (coef exp) than press enter";
		in >> coef >> exp;
		cur->Set(coef, exp);
	}

	return in;
}

std::ostream& operator<< (std::ostream& out, Polynomial& x)
{
	if (x.poly == nullptr)
	{
		out << "0";
		return out;
	}

	Node *cur = x.poly;

	// each ,c,e
	do
	{
		if (cur->GetExp() == 0)
		{
			out << cur->GetCoef() << "+";
			cur = cur->GetNext();
		}
		else
		{
			out << cur->GetCoef() << "x^" << cur->GetExp() << "+";
			cur = cur->GetNext();
		}
	} while (cur != x.poly);
	out<<'\b';

	return out;
}

double Polynomial::Evaluate (double x) const
{
	double answer = 0;
	Node *cur = this->poly;

	do
	{
		answer += cur->GetCoef() * (cur->GetExp() == 0 ? 1.0 : pow(x, (double)cur->GetExp()));
		cur = cur->GetNext();
	} while (cur != this->poly);
	
	return answer;
}

Polynomial& Polynomial::operator= (const Polynomial& a)
{
	if (this->poly != nullptr)
	{
		this->poly->RetNode();
		this->poly = nullptr;
	}
	
	// a little hacky here: copy a and use its poly
	Polynomial copied = Polynomial(a);
	Node *poly = copied.poly;
	
	// prevents it from destructing it
	copied.poly = nullptr;

	this->poly = poly;

	return (*this);
}

Polynomial Polynomial::operator+(const Polynomial& b) const
{
	// If one of them is empty
	if (this->poly == nullptr)
	{
		return Polynomial(b);
	}
	else if (b.poly == nullptr)
	{
		return Polynomial(*this);
	}

	// otherwise
	Polynomial p = Polynomial(*this);

	// Iterate through all coefs in b: add them into p by seeking an appropriate position for each node in b
	Node *nodeB = b.poly;
	
	do
	{
		Node *nodeP = p.poly;
		while (true)
		{
			// if b node has larger exp: insert it before current node, seek next b node
			// this way we don't need to modify the chain start
			if (nodeB->GetExp() > nodeP->GetExp())
			{
				Node::InsertEmpty(&nodeP);
				Node *newNode = nodeP->GetNext();
				newNode->Set(nodeP->GetCoef(), nodeP->GetExp());
				nodeP->Set(nodeB->GetCoef(), nodeB->GetExp());
				break;
			}

			// if b node has equal exp: add together the coefs, seek next b node
			if (nodeB->GetExp() == nodeP->GetExp())
			{
				nodeP->Set(nodeP->GetCoef() + nodeB->GetCoef(), nodeP->GetExp());
				break;
			}

			// or maybe this term is the smallest term present
			if (nodeP->GetNext() == p.poly)
			{
				Node::InsertEmpty(&nodeP);
				Node *newNode = nodeP->GetNext();
				newNode->Set(nodeB->GetCoef(), nodeB->GetExp());
				nodeP->Set(newNode);
				break;
			}

			// else: continue iteration
			nodeP = nodeP->GetNext();
		}

		nodeB = nodeB->GetNext();
	} while (nodeB != b.poly);

	p.trimZero();
	return p;
}

Polynomial Polynomial::operator-(const Polynomial& b) const
{
	Polynomial p = Polynomial(*this);

	Polynomial negOne = Polynomial();
	negOne.poly = Node::GetNode();
	negOne.poly->Set(-1, 0, negOne.poly);
	
	p = p + (b * negOne);
	p.trimZero();
	return p;
}

Polynomial Polynomial::operator* (const Polynomial& b) const
{
	Polynomial p = Polynomial();

	Node *nodeSelf = this->poly;
	Node *nodeB = b.poly;

	do
	{
		do
		{
			Node *product = Node::GetNode();
			product->Set(nodeSelf->GetCoef() * nodeB->GetCoef(), nodeSelf->GetExp() + nodeB->GetExp(), product);
			Polynomial productTerm = Polynomial();
			productTerm.poly = product;
			p = p + productTerm;

			nodeB = nodeB->GetNext();

		} while (nodeB != b.poly);
		

		nodeSelf = nodeSelf->GetNext();
	} while (nodeSelf != this->poly);
	
	p.trimZero();
	return p;
}