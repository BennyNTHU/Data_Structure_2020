#include <iostream>
#include <math.h>

using namespace std;

class Polynomial;

class Term{
friend class Polynomial;
public:
  Term(){coef = 0; exp = 0;};
  Term(float c, int e){coef = c; exp = e;}
  friend ostream &operator<<( ostream &output, const Term &term ){//output << a Term
    if(term.exp == 0)
      output << term.coef;
    else if(term.exp == 1)
      output << term.coef << "x";
    else
      output << term.coef << "x^" << term.exp;
    return output;
  }
private:
  float coef;  //coefficient
  int exp;     //exponent
};

class Polynomial {
// p(x) = a0 x^e0 + ï¿?+ an x^en
// where ai is nonzero float and ei is non-negative int
private:
  Term * termArray;
  int capacity;  //size of termArray
  int terms;     //number of nonzero terms

public:
  Polynomial(){//construct the polynomial p(x) = 0
    capacity=5; terms=0;
    termArray=new Term[capacity];
    termArray[0].coef=0; termArray[0].exp=0;
  }
  Polynomial(Term* arr, int n){//arr[]: existed termArray, n:terms of arr
    terms = n;
    capacity = n;
    termArray=new Term[capacity];
    copy(arr, arr+n, termArray);
    delete [] arr;
  }
  Polynomial Add(Polynomial poly);
  //return the sum of *this and poly
  void reset(){
    terms = 0; capacity = 5;
    delete[] termArray;
    termArray = new Term[5];
  }
  Polynomial Mult(Polynomial poly);
  //return the product of *this and poly
  float Eval(float f );
  //Evaluate the polynomial *this at f and return the results
  void NewTerm(const float theCoeff, const int theExp);
  //Add new term at the end of *this
  friend ostream &operator<<( ostream &output, const Polynomial &poly ){//output << a Poly
    for(int i=0; i<(poly.terms)-1;i++){
      output << poly.termArray[i] << " + ";
    }
    output << poly.termArray[(poly.terms)-1];
    return output;
  }
  friend istream &operator>>( istream  &input, Polynomial &poly ){//input >> a Poly
    cout << "How many terms in the Polynomial?" << endl;
    int aterms;//terms of input poly A
    input >> aterms;

    //store input in buff
    Term* buff = new Term[aterms];

    float temp_coef;
    int temp_exp;
    cout << "Enter the coef and exp of the polynomial alternatively." << endl;
    for(int i=0; i<aterms; i++){
      input >> temp_coef >> temp_exp;
      buff[i] = Term(temp_coef, temp_exp);
    }

    poly = Polynomial(buff, aterms);
    return input;
  }
};


void Polynomial::NewTerm(const float theCoeff, const int theExp)
{// Add a new term to the end of termArray
    if (terms == capacity)  // termArray (of c) is full
    {// double the capacity of termArray
        capacity *= 2;
        Term *temp = new Term[capacity];
        copy(termArray, termArray + terms, temp);
        delete [] termArray ; // delete allocated old memory
        termArray = temp;
    }
    termArray [terms].coef = theCoeff;
    termArray [terms++].exp = theExp;
}

Polynomial Polynomial::Add(Polynomial b)
{//c=a.Add(b)
  Polynomial c; //c.terms = 0
  int aPos = 0, bPos = 0;
  while ((aPos < terms) && (bPos < b.terms)){
    if (termArray[aPos].exp == b.termArray[bPos].exp) {
      float t = termArray[aPos].coef + b.termArray[bPos].coef;
      c.NewTerm (t, termArray [aPos].exp);
      aPos++; bPos++;
    }
    else if (termArray[aPos].exp < b.termArray[bPos].exp) {
      c.NewTerm (b.termArray[bPos].coef, b.termArray[bPos].exp);
      bPos++;
    }
    else {
      c.NewTerm (termArray[aPos].coef, termArray[aPos].exp);
      aPos++;
    }
  }
  //add in remaining terms of *this
  for ( ; aPos < terms ; aPos++)//output the remaining terms
    c.NewTerm (termArray[aPos].coef, termArray[aPos].exp);

  //add in remaining terms of b
  for ( ; bPos < b.terms ; bPos++)//output remaining terms
    c.NewTerm (b.termArray[bPos].coef, b.termArray[bPos].exp);

  return c;
}


Polynomial Polynomial::Mult(Polynomial b)
{//c=a.mult(b)
  Polynomial c; //c.terms = 0

  int aPos = 0, bPos = 0;//index in poly a, b
  Polynomial temp;// store a.termArray[i] * b
  for( ;aPos<terms;aPos++){
    for(;bPos<b.terms;bPos++){
      float tempcoef = termArray[aPos].coef * b.termArray[bPos].coef;
      int tempexp = termArray[aPos].exp + b.termArray[bPos].exp;
      temp.NewTerm (tempcoef, tempexp);
    }
    c = c.Add(temp);
    bPos = 0;
    temp.reset();// temp = 0
  }
  return c;
}

float Polynomial::Eval (float f)
{
  float eval=0;//answer
  for(int i=0;i<terms;i++){
    eval += termArray[i].coef * pow(f,termArray[i].exp);
  }
  return eval;
}

int main()
{
  Polynomial a, b, c, d;//(aarray, aterms);

  cin >> a;
  cout << "Another Polynomial: " << endl;
  cin >> b;

  cout << "A= " << a << endl;
  cout << "B= " << b << endl;

  c = a.Add(b);
  d = a.Mult(b);
  cout << "C = A + B = " << c << endl;
  cout << "D = A * B = " << d << endl;
  cout << "D(1.01) = " << d.Eval(1.01) << endl;

  return 0;
}
