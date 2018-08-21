#pragma once
#include <iostream>
using namespace std;


template <class KeyType, class DataType>
struct Node
{
	KeyType *key=NULL;//������������
	DataType info;
	Node* next=NULL;
	Node(int D, DataType x = DataType())//dΪ�������λ��
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
	Node<KeyType, DataType>* f=NULL;//���е�ͷָ��
	Node<KeyType, DataType>* e=NULL;//���е�βָ��
};

template <class DataType>
void radixSort(Node<char,DataType>* plist,int d, int r)//���������㷨��plistӦ��ͷ���ʹ�ã�,dΪ�������λ��,rΪ������Ļ���
{
	int i, j, k;
	Node<char, DataType>*p; Node<char, DataType>* head = plist->next; 
	Queue<char, DataType> *queue = new Queue<char, DataType>[r];
	for (j = d - 1; j >= 0; --j)
	{
		for (i = 0; i < r; ++i) { queue[i].f = NULL; queue[i].e = NULL; }//��ն���
		for (p = head; p != NULL; p = p->next)
		{
			if (p->key[j] == 0) { k = 0; }
			else { k = p->key[j] - 'A' + 1;  }//��������ĵ�j����������
			if (queue[k].f == NULL) { queue[k].f = p; }//����Ϊ������Ϊ��ͷָ��
			else { (queue[k].e)->next = p; }//�ӵ�����k��β��
			queue[k].e = p;
		}
		for (i = 0; queue[i].f == NULL; ++i);//�ҵ���һ���ǿն���
		p = queue[i].e;head = queue[i].f;//headΪ�ռ������ͷָ��
		for (i++; i < r; ++i)
		{
			if (queue[i].f != NULL) { p->next = queue[i].f;p = queue[i].e; }
			p->next = NULL;
		}	
	}
	plist->next = head;
}

