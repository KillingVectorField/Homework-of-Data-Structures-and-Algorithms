// Sort_homework.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "SortObject.h"
#include "RadixList.h"
#include <string>
#define length 10

template <class DataType>
SortObject<int, DataType>* Produce_Random_Sort(int max, int n)
{
	SortObject<int, DataType>* p = new SortObject<int, DataType>(max);
	for (int i = 0; i < n; ++i)
	{
		p->record[i].key = rand();
		++(p->n);
	}
	return p;
}

char* type_in(char* t,int d,string x)//d为排序码的位数
{
	int size = x.size();
	if (size > d) { cout << "Overflow!" << endl; return NULL; }
	for (int i = 0; i < size; ++i)
	{
		t[i] = x[i];
	}
	for (int i = size; i < d; ++i)
	{
		t[i] = 0;
	}
	return t;
}

template <class DataType>
void get_RadixList(Node<char, DataType>* plist, int num,int d)
{
	Node<char, DataType>*p = plist;//带头结点的链表
	string x;
	for (int i = 0; i < num; ++i)
	{
		p->next= new Node<char, DataType>(d);
		p = p->next;
		cin >> x;
		type_in(p->key, d, x);
	}
}

int main()
{
	/*srand(0);
	SortObject<int, int>* Random = Produce_Random_Sort<int>(100, 100);
	cout << *Random;
	Random->bubbleSort_2();
	cout << *Random;*/
	Node<char, string>* plist = new Node<char, string>(length);
	/*type_in(plist->key, 10, "start");
	cout << plist->key << "a";*/
	int x;
	cout << "How many words?" << endl;
	cin >> x;
	get_RadixList(plist, x, length);
	cout << plist;
	radixSort(plist,length, 27);
	cout << plist;
    return 0;
}

