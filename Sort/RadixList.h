#pragma once
#include <iostream>
using namespace std;


template <class KeyType, class DataType>
struct Node
{
	KeyType *key=NULL;//排序码是数组
	DataType info;
	Node* next=NULL;
	Node(int D, DataType x = DataType())//d为排序码的位数
	{
		if (D)
		{
			key = new KeyType[D];
		}
		else key = NULL;
		info = x;
	}
	friend ostream & operator <<(ostream & os, const Node *c)
	{
		Node*p;
		for (p = c->next; p != NULL; p = p->next)
		{
			os << keyname << p->key << " " << infoname << p->info << endl;
		}
		return os;
	}
};

template <class KeyType, class DataType>
struct Queue
{
	Node<KeyType, DataType>* f=NULL;//队列的头指针
	Node<KeyType, DataType>* e=NULL;//队列的尾指针
};

template <class DataType>
void radixSort(Node<char,DataType>* plist,int d, int r)//基数排序算法（plist应对头结点使用）,d为排序码的位数,r为排序码的基数
{
	int i, j, k;
	Node<char, DataType>*p; Node<char, DataType>* head = plist->next; 
	Queue<char, DataType> *queue = new Queue<char, DataType>[r];
	for (j = d - 1; j >= 0; --j)
	{
		for (i = 0; i < r; ++i) { queue[i].f = NULL; queue[i].e = NULL; }//清空队列
		for (p = head; p != NULL; p = p->next)
		{
			if (p->key[j] == 0) { k = 0; }
			else { k = p->key[j] - 'A' + 1;  }//按排序码的第j个分量分配
			if (queue[k].f == NULL) { queue[k].f = p; }//队列为空则设为队头指针
			else { (queue[k].e)->next = p; }//接到队列k的尾部
			queue[k].e = p;
		}
		for (i = 0; queue[i].f == NULL; ++i);//找到第一个非空队列
		p = queue[i].e;head = queue[i].f;//head为收集链表的头指针
		for (i++; i < r; ++i)
		{
			if (queue[i].f != NULL) { p->next = queue[i].f;p = queue[i].e; }
			p->next = NULL;
		}	
	}
	plist->next = head;
}

