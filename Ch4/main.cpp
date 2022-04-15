#include <iostream>
#include <map>
#include <string>
#include "poly.h"

using namespace std;

map<string, Polynomial> polynomials;

void createPoly();
void deletePoly();
void addPoly();
void subPoly();
void mulPoly();
void evalPoly();
void outputPoly();
void assignPoly();
void listPoly();


int main()
{
	while (true)
	{
		std::cout << "\n\n";
		std::cout << "         - Available Operations -         \n";
		std::cout << "- All IDs should not contain white spaces -\n";
		std::cout << ":: [c] create a new polynomial\n";
		std::cout << ":: [d] delete an existing polynomial\n";
		std::cout << ":: [a] create a new polynomial by adding two\n";
		std::cout << ":: [s] create a new polynomial by subtracting one from another\n";
		std::cout << ":: [m] create a new polynomial by multiplying two\n";
		std::cout << ":: [e] evaluate an existing polynomial\n";
		std::cout << ":: [o] output representation of a polynomial\n";
		std::cout << ":: [g] assign one polynomial to another\n";
		std::cout << ":: [l] list all polynomials\n";
		std::cout << ":: ";

		char op;
		cin >> op;
		std::cout << "\n\n";

		switch (op)
		{
			case 'c':
				createPoly();
				break;
			case 'd':
				deletePoly();
				break;
			case 'a':
				addPoly();
				break;
			case 's':
				subPoly();
				break;
			case 'm':
				mulPoly();
				break;
			case 'e':
				evalPoly();
				break;
			case 'o':
				outputPoly();
				break;
			case 'g':
				assignPoly();
				break;
			case 'l':
				listPoly();
				break;
			default:
				std::cout << "Invalid. Please try again.\n";
		}
	}
}

void createPoly()
{
	Polynomial p;
	string id;
	std::cout << "[Create] Enter ID: ";
	cin >> id;

	if (polynomials.find(id) != polynomials.end())
	{
		std::cout << "[Create] ID already exists!\n";
		return;
	}

	std::cout << "[Create] Polynomial: ";
	cin >> p;

	polynomials.emplace(id, p);
}

void deletePoly()
{
	string id;
	std::cout << "[Delete] Enter ID: ";
	cin >> id;

	map<string, Polynomial>::iterator it = polynomials.find(id);
	if (it == polynomials.end())
	{
		std::cout << "[Delete] ID does not exist!\n";
		return;
	}
	else
	{
		std::cout << "[Delete] Successfully deleted poly: " << it->second << "\n";
		polynomials.erase(it);
	}
}

void addPoly()
{
	string idA;
	string idB;
	string id;
	Polynomial p;

	std::cout << "[Add] Perform polynomial addition p = a + b.\n";
	std::cout << "[Add] Enter ID of a: ";
	cin >> idA;
	std::cout << "[Add] Enter ID of b: ";
	cin >> idB;
	std::cout << "[Add] Enter ID of p: ";
	cin >> id;

	map<string, Polynomial>::iterator itA = polynomials.find(idA);
	map<string, Polynomial>::iterator itB = polynomials.find(idB);
	map<string, Polynomial>::iterator it = polynomials.find(id);
	if (itA == polynomials.end() || itB == polynomials.end() || it != polynomials.end())
	{
		std::cout << "[Mul] A error occurred! Make sure a and b exist and the id of p is not yet taken.\n";
		return;
	}

	p = itA->second + itB->second;
	polynomials.emplace(id, p);

	std::cout << "[Add] A = " << itA->second << "\n";
	std::cout << "[Add] B = " << itB->second << "\n";
	std::cout << "[Add] P = " << p << "\n";
}

void subPoly()
{
	string idA;
	string idB;
	string id;
	Polynomial p;

	std::cout << "[Sub] Perform polynomial subtraction p = a - b.\n";
	std::cout << "[Sub] Enter ID of a: ";
	cin >> idA;
	std::cout << "[Sub] Enter ID of b: ";
	cin >> idB;
	std::cout << "[Sub] Enter ID of p: ";
	cin >> id;

	map<string, Polynomial>::iterator itA = polynomials.find(idA);
	map<string, Polynomial>::iterator itB = polynomials.find(idB);
	map<string, Polynomial>::iterator it = polynomials.find(id);
	if (itA == polynomials.end() || itB == polynomials.end() || it != polynomials.end())
	{
		std::cout << "[Mul] A error occurred! Make sure a and b exist and the id of p is not yet taken.\n";
		return;
	}

	p = itA->second - itB->second;
	polynomials.emplace(id, p);

	std::cout << "[Sub] A = " << itA->second << "\n";
	std::cout << "[Sub] B = " << itB->second << "\n";
	std::cout << "[Sub] P = " << p << "\n";
}

void mulPoly()
{
	string idA;
	string idB;
	string id;
	Polynomial p;

	std::cout << "[Mul] Perform polynomial multiplication p = a * b.\n";
	std::cout << "[Mul] Enter ID of a: ";
	cin >> idA;
	std::cout << "[Mul] Enter ID of b: ";
	cin >> idB;
	std::cout << "[Mul] Enter ID of p: ";
	cin >> id;

	map<string, Polynomial>::iterator itA = polynomials.find(idA);
	map<string, Polynomial>::iterator itB = polynomials.find(idB);
	map<string, Polynomial>::iterator it = polynomials.find(id);
	if (itA == polynomials.end() || itB == polynomials.end() || it != polynomials.end())
	{
		std::cout << "[Mul] A error occurred! Make sure a and b exist and the id of p is not yet taken.\n";
		return;
	}

	p = itA->second * itB->second;
	polynomials.emplace(id, p);

	std::cout << "[Mul] A = " << itA->second << "\n";
	std::cout << "[Mul] B = " << itB->second << "\n";
	std::cout << "[Mul] P = " << p << "\n";
}

void evalPoly()
{
	string id;
	double x;
	std::cout << "[Eval] Enter ID: ";
	cin >> id;
	std::cout << "[Eval] Enter x: ";
	cin >> x;

	if (polynomials.find(id) == polynomials.end())
	{
		std::cout << "[Eval] The ID does not exist!\n";
		return;
	}

	std::cout << "[Eval] P = " << polynomials.at(id) << "\n";
	std::cout << "[Eval] P(" << x << ") = " << polynomials.at(id).Evaluate(x) << "\n";
}

void outputPoly()
{
	string id;
	std::cout << "[Output] Enter ID: ";
	cin >> id;

	map<string, Polynomial>::iterator it = polynomials.find(id);
	if (it == polynomials.end())
	{
		std::cout << "[Output] The ID does not exist!\n";
		return;
	}

	std::cout << "[Output] P = " << it->second << "\n";
}

void assignPoly()
{
	std::cout << "[Assign] Perform assignment p = a.\n";

	string idP;
	string idA;
	std::cout << "[Assign] Enter ID of p: ";
	cin >> idP;
	std::cout << "[Assign] Enter ID of a: ";
	cin >> idA;

	map<string, Polynomial>::iterator itP = polynomials.find(idP);
	map<string, Polynomial>::iterator itA = polynomials.find(idA);
	if (itA == polynomials.end() || itP == polynomials.end())
	{
		std::cout << "[Assign] A error occurred! Make sure a and b exist.\n";
		return;
	}

	std::cout << "[Assign] Before assignment, P = " << itP->second << "\n";
	itP->second = itA->second;
	std::cout << "[Assign] P = " << itP->second << "\n";
	std::cout << "[Assign] A = " << itA->second << "\n";
}

void listPoly()
{
	for (auto it : polynomials)
	{
		std::cout << it.first << " = " << it.second << "\n";
	}
}
