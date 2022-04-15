//EECS2040 Data Structure Hw #6 (Chapter 7 Sorting, Chapter 8 Hashing)
//due date 6/20/2021
//106061218, Cheng-En Lee
//Part 2, problem 1

#include <iostream>
#include <algorithm>
#include <math.h>
#include <random>
#include <cstring>

using namespace::std;

void print_array();
template <class T> void InsertionSort(T *a, const int n);
template <class T> void QuickSort(T *a, const int left, const int right);
template <class T> void MergeSort(T *a, const int n);
template <class T> void MergePass(T *a, T *b, const int n, const int s);
template <class T> void Merge(T *a, T *b, const int k, const int m, const int n);
template <class T> int rMergeSort(T* a, int* link, const int left, const int right);
template <class T> int ListMerge(T* a, int* link, const int start1, const int start2);
template <class T> void HeapSort(T *a, const int n);
template <class T> void Adjust(T *a, const int root, const int n);

int I[20];
double D[20];
char C[20];

int main(void)
{
    int link[20]; // for recursive merge sort
    char word[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";
    const int word_length = 62; // The length of above string

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(0, 50);

    for (int i = 0; i < 20; i++) 
    {
        I[i] = std::rand()/((RAND_MAX + 1u)/50);
        C[i] = 'a' + std::rand() % 26;
        D[i] = dis(gen);
    }

    cout << "initial array: " << endl;
    print_array();

    cout << "Insertion sort: " << endl;
    InsertionSort(I, 19);
    InsertionSort(C, 19);
    InsertionSort(D, 19);
    print_array();
    cout << '\n';

    for (int i = 0; i < 20; i++) 
    {
        I[i] = std::rand()/((RAND_MAX + 1u)/50);
        C[i] = 'a' + std::rand() % 26;
        D[i] = dis(gen);
    }

    cout << "initial array: " << endl;
    print_array();

    cout << "QuickSort: " << endl;
    QuickSort(I, 1, 19);
    QuickSort(C, 1, 19);
    QuickSort(D, 1, 19);
    print_array();
    cout << '\n';

    for (int i = 0; i < 20; i++) 
    {
        I[i] = std::rand()/((RAND_MAX + 1u)/50);
        C[i] = 'a' + std::rand() % 26;
        D[i] = dis(gen);
    }

    cout << "initial array: " << endl;
    print_array();

    cout << "MergeSort: " << endl;
    MergeSort(I, 19);
    MergeSort(C, 19);
    MergeSort(D, 19);
    print_array();
    cout << '\n';

    for (int i = 0; i < 20; i++) 
    {
        I[i] = std::rand()/((RAND_MAX + 1u)/50);
        C[i] = 'a' + std::rand() % 26;
        D[i] = dis(gen);
    }

    cout << "initial array: " << endl;
    print_array();

    cout << "Recursive merge sort: " << endl;
    for (int i = 0; i < 20; i++)
        link[i] = 0;
    int a = rMergeSort(I, link, 1, 19);
    for (int i = 1; i < 20; i++)
        for (int j=1; j<20; j++)
            if (link[j] == i)
                cout << I[j] << ' ';
    cout << endl;
    for (int i = 0; i < 20; i++)
        link[i] = 0;
    int b = rMergeSort(C, link, 1, 19);
    for (int i = 1; i < 20; i++)
        for (int j=1; j<20; j++)
            if (link[j] == i)
                cout << C[j] << ' ';
    cout << endl;
    for (int i = 0; i < 20; i++)
        link[i] = 0;
    int c = rMergeSort(D, link, 1, 19);
    for (int i = 1; i < 20; i++)
        for (int j=1; j<20; j++)
            if (link[j] == i)
                cout << D[j] << ' ';
    cout << endl;
    cout << '\n';

    for (int i = 0; i < 20; i++) 
    {
        I[i] = std::rand()/((RAND_MAX + 1u)/50);
        C[i] = 'a' + std::rand() % 26;
        D[i] = dis(gen);
    }

    cout << "initial array: " << endl;
    print_array();

    cout << "HeapSort: " << endl;
    HeapSort(I, 19);
    HeapSort(C, 19);
    HeapSort(D, 19);
    print_array();
    cout << '\n';

    return 0;
}

void print_array()
{
    for (int i = 0; i < 20; i++) 
    {
        cout << I[i] << ' ';
    }
    cout << endl;
    for (int i = 0; i < 20; i++) 
    {
        cout << C[i] << ' ';
    }
    cout << endl;
    for (int i = 0; i < 20; i++) 
    {
        cout << D[i] << ' ';
    }
    cout << endl;
}

template <class T>
void InsertionSort(T *a, const int n)   // sort a[1:n] into nondecreasing order
{
    int i=0;

    for (int j = 2; j <= n ; j++)
    {
        a[0] = a[j];
        for (i = j - 1; a[i] > a[0]; i--) 
        {
            a[i + 1] = a [i];
        }
        a[i + 1] = a[0];  
    }  
}

template <class T>
void QuickSort(T *a, const int left, const int right)   // sort a[left:right] into nondecreasing, a[left] as pivot
{
    /*T med[3] = {a[left], a[(left+right)/2], a[right]};
    sort(med, med+2);*/

    if (left < right) 
    {
        T & pivot = a[left];
        int i = left;
        int j = right + 1;
        do {
            do j--; while (a[j] > pivot);  //find a key ≤pivot
            do i++; while (a[i] <= pivot); //find a key >pivot
                     
            if (i < j) swap(a[i], a[j]);
        } while (i < j);
        swap(pivot, a[j]); //place the pivot between 2 lists
        QuickSort(a, left, j - 1);  // recursion
        QuickSort(a, j + 1, right); // recursion
    }
}

template <class T>
void MergeSort(T *a, const int n)   // sort a[1:n] into non-decreasing order
{ 
    T *tempList = new T[n+1];

    for (int s = 1; s < n; s *= 2)  // s is the length of the currently merged sublist
    {
        MergePass(a, tempList, n, s);
        s *= 2;
        MergePass(tempList, a, n, s);   
    }
    delete [] tempList;
}

template <class T>
void MergePass(T *a, T *b, const int n, const int s)
{   
    int i=0;
    //adjacent pairs of sublist of size s are merged from a to b. n = # records in a
    //i the first position in first of the sublists merged
    //enough elements for 2 sublists of length s?
    for (i = 1; i <= n-(2*s)+1; i+= 2*s) 
    {
	    Merge(a, b, i, i+s-1, i+(2*s)-1);
    }
    // merge remaining lists of size < 2*s
    if ((i + s-1) < n) //one full and one partial lists
        Merge(a, b, i, i+s-1, n);
    else               //only one partial lists remained
        copy(a+i, a+n+1, b+i);
}

template <class T>
void Merge(T *a, T *b, const int k, const int m, const int n)   // a[k:m], a[m+1:n] are sorted, merged to b[k:n]
{
    int i1=0, i2=0, i3=0;

    for (i1 = k, i2 = m+1, i3 = k;  i1 <= m && i2 <= n; i3++) 
    {
        if (a[i1] <= a [i2]) 
        {
            b [i3] = a [i1];
            i1++;
        } 
        else 
        {
            b [i3] = a [i2];
            i2++;
        }
    }
    if(i2>n) copy(a+i1, a+m+1, b+i3);  // copy remaining records, if any, of 1st sublist
    if(i1>m) copy(a+i2, a+n+1, b+i3);  // copy remaining records, if any, of 2nd sublist
}

template <class T>
int rMergeSort(T* a, int* link, const int left, const int right)
{   
    // 要排序的是a[left:right]。對於所有i，link[i] 初始化為0。
    // rMerge回傳排序好的鏈的第一個元素之索引值。
    if (left >= right) 
        return left; //base case

	int mid = (left + right) /2;

	return ListMerge(a, link,
   		rMergeSort(a, link, left, mid),         // 排序左半邊
  		rMergeSort(a, link, mid + 1, right));   // 排序右半邊
}

template <class T>
int ListMerge(T* a, int* link, const int start1, const int start2)
{   
    // 兩個排序好的鏈分別從start1及start2開始，將它們合併
    // 將link[0]當作一個暫時的標頭。回傳合併好的鏈的開頭。
	int iResult = 0; // 結果鏈的最後一筆記錄
    int i1=0, i2=0;

	for (i1 = start1, i2 =start2; i1 && i2;)
		if (a[i1] <= a[i2]) 
        {
			link[iResult] = i1;
			iResult = i1; 
            i1 = link[i1];
        }
		else 
        {
			link[iResult] = i2;
			iResult = i2; 
            i2 =link[i2];	
        }
	
	if (i1 == 0)    // 將其餘的記錄附接至結果鏈 
        link[iResult] = i2;
	else 
        link[iResult] = i1;

	return link[0];
}

template <class T>
void HeapSort(T *a, const int n)
{
    // sort a[1..n] into non-decreasing order
    // a[n/2] is the parent of the last node, a[n]
    for (int i = n/2; i >= 1; i--) // buttom-up heapification
       Adjust(a, i, n); // make the tree rooted at i be a max heap

    for (int i = n-1; i >= 1; i--) 
    {
       swap(a[1], a[i+1]); // move one record from heap to list
       Adjust(a, 1, i);    // heapify
    }
}

template <class T>
void Adjust(T *a, const int root, const int n)
{
    // two subtrees are max heaps already	
    // same procedure as the trickling-down procedure
    T e = a[root];
    int j=0;
    
    for (j = 2*root; j <= n; j *=2) //2*root is root's left child
    {
        if (j < n && a[j] < a[j+1]) // j and j+1 are siblings
            j++; // make j be the max child
        if (e >= a[j]) 
            break; 
        a[j / 2] = a[j]; // move jth record up the path
    }
    a[j / 2] = e;
}
