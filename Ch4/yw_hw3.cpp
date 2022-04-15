#include <iostream>
using namespace std;

template <class T> class List;
template <class T>
class Node
{
friend class List<T>;
private:
  T data;
  Node* link;
public:
  Node(){link = NULL;}
  Node(const T& item, Node<T> * ptr){
    data = item; link = ptr;
  }
};

template <class T>
class List{
public:
  List(){first = 0;}
  ~List(){
    Node<T>* temp = first;//temp: traverse
    while(first != NULL){
      first = first->link;
      delete temp;
      temp = first;
    }
  }
  friend ostream &operator<<(ostream &output,  const List &list){//output << List
    if(list.first == 0){
      cout << "Empty List!" << endl;
    }
    else{
      for(List<T>::Iterator i=list.Begin(); i!=list.End(); i++){
        output << *i << " ";
      }
    }
    cout << endl;
    return output;
  }
  void InsertFront(const T& e);
  void DeleteFront();
  void DeleteBack();
  T& Front() const;
  T& Back() const;
  T& Get(const int k) const;
  void Delete(const int k);
  void Insert(const int k, const T& e);

  void InsertBack(const T& e);
  void Concatenate(List<T>& b);
  void Reverse();

  class Iterator{
  friend class List;
  public: //typedefs required by C++ for a forward iterator
    //Constructor
    Iterator(Node<T>* startNode = 0)
      {current = startNode;}
    //Dereferencing operators
    T& operator *() const {return current -> data;}
    T* operator ->() const {return &current -> data;}
    //Increment
    Iterator& operator ++() //preincrement
      {current = current ->link; return *this;}
    Iterator& operator ++(int) //postincrement
      {Iterator old = *this;
       current = current ->link; return old;}
    //Equality test
    bool  operator!=(const Iterator r)
      {return current != r.current;}
    bool  operator==(const Iterator r)
      {return current == r.current;}
  private:
    Node <T> * current;
  };
  Iterator Begin() const{return Iterator(first);}
  Iterator End() const{return Iterator(0);}
private:
  Node<T>* first;
};

template<class T>
void List<T>::InsertFront(const T& e)
{
  if(first == 0){
    first = new Node<T>(e, 0);
  }
  else{
    Node<T> * temp = new Node<T>(e, first);
    first = temp;
  }
}

template<class T>
void List<T>::DeleteFront()
{
  Node<T> *temp = first;
  first = first->link;
  delete temp;
}

template<class T>
void List<T>:: DeleteBack()
{
  Node<T> *temp = first, *todel;
  while(temp->link->link != NULL){
    temp = temp->link;
  }
  todel = temp->link;
  temp->link = 0;
  delete todel;
}

template<class T>
T& List<T>::Front() const
{
  return first->data;
}

template<class T>
T& List<T>::Back() const
{
  Node<T> *temp = first;
  while(temp->link != NULL){
    temp = temp->link;
  }
  return temp->data;
}

template<class T>
T& List<T>::Get(const int k) const
{
  Node<T> *temp = first;
  for(int i=0; i<k-1; i++){
    temp = temp->link;
  }
  return temp->data;
}

template<class T>
void List<T>::Delete(const int k)
{

  if(k == 1){
    Node<T> *todel = first;
    first = first->link;
    delete todel;
  }
  else{
    Node<T> *temp = first, *todel;
    for(int i=0; i<k-2; i++){
      temp = temp->link;
      if(temp == NULL){
        cout << "No such element!" << endl;
        return;
      }
    }
    todel = temp->link;
    temp->link = temp->link->link;
    delete todel;
  }
}

template<class T>
void List<T>::Insert(const int k, const T& e)
{
  Node<T> *temp = first;
  if(k == 1){
    InsertFront(e);
  }
  else{
    for(int i=0; i<k-2; i++){
      temp = temp->link;
      if(temp == NULL){
        cout << "No such lacation!" << endl;
        return;
      }
    }
    Node<T> *toins = new Node<T>(e, temp->link);
    temp->link = toins;
  }
}


template<class T>
void List<T>::InsertBack(const T& e)
{
  if(first == 0){
    first = new Node<T>(e, NULL);
  }
  else{
    Node<T> *temp = first;
    while(temp->link != NULL){
      temp = temp->link;
    }
    Node<T> *toins = new Node<T>(e, NULL);
    temp->link = toins;
  }
}

template<class T>
void List<T>::Concatenate(List<T>& b)
{
  Node<T> *temp = first;
  while(temp->link !=NULL){
    temp = temp->link;
  }
  temp->link = b.first;
}

template<class T>
void List<T>::Reverse()
{
  if((first == 0) || (first->link == 0)){
    return;
  }
  Node<T> *temp = first, *tagaft, *tagpre;// tag: save link
  tagaft = temp->link;
  temp->link = NULL;
  tagpre = temp;
  temp = tagaft;
  while(temp->link != NULL){
    tagaft = temp->link;
    temp->link = tagpre;
    tagpre = temp;
    temp = tagaft;
  }
  temp->link = tagpre;
  first = temp;
}

int main()
{
  List<int> Intlist;

  cout << "InsertFront() from 0 to 9." << endl;
  for(int i=0; i<10; i++){
    Intlist.InsertFront(i);
  }
  cout << Intlist;

  cout << "DeleteFront():" << endl;
  Intlist.DeleteFront();
  cout << Intlist;

  cout << "DeleteBack():" << endl;
  Intlist.DeleteBack();
  cout << Intlist;

  cout << "Front(): ";
  cout << Intlist.Front() << endl;

  cout << "Back(): ";
  cout << Intlist.Back() << endl;

  cout << "Get(3): ";
  cout << Intlist.Get(3) << endl;

  Intlist.Delete(3);
  cout << "Intlist_Delete(3): ";
  cout << Intlist;

  Intlist.Insert(3, 6);
  cout << "Intlist_Insert(3, 6): ";
  cout << Intlist;

  Intlist.InsertBack(0);
  cout << "Intlist_InsertBack(0): ";
  cout << Intlist;

  List<int> Intlist2;
  for(int i=-1; i>-9; i--){
    Intlist2.InsertBack(i);
  }
  cout << "Intlist2: " << Intlist2;

  Intlist.Concatenate(Intlist2);
  cout << "Intlist_Intlist2: " << Intlist;

  Intlist.Reverse();
  cout << "Intlist_Reverse: ";
  cout << Intlist;

  Intlist.~List();
  cout << "Intlist_~List: ";
  cout << Intlist;

cout << "end";
  return 0;
}








