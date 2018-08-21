#pragma once
#include <iostream>
using namespace std;
#define keyname "�ؼ��֣�"
#define infoname "���ݣ�"

unsigned int comparing_times = 0, moving_times = 0;

template <class KeyType, class DataType>
struct RecordNode
{
	KeyType key;
	DataType info;
	RecordNode(KeyType k=KeyType(),DataType i=DataType()):key(k),info(i){}
	friend ostream & operator <<(ostream & os, const RecordNode &c)
	{
		os << keyname << c.key << " " << infoname << c.info;
		return os;
	}
};

template <class KeyType, class DataType>
void merge(RecordNode<KeyType, DataType>* origin, RecordNode<KeyType, DataType>* newrec, int low, int m,int high)//����鲢�㷨
{
	int i, j, k;
	i = low; j = m + 1; k = low;
	while ((i <= m) && (j <= high))//�����������ļ��еĵ�һ����¼��ѡ��С�ļ�¼
	{
		if(origin[i].key <= origin[j].key){newrec[k] = origin[i]; ++k; ++i; }
		else { newrec[k] = origin[j]; ++k; ++j; }
	}
	while (i <= m) { newrec[k] = origin[i]; ++k; ++i; }//���Ƶ�һ���ļ���ʣ���¼
	while (j <= high) { newrec[k] = origin[j]; ++k; ++j; }//���Ƶڶ����ļ���ʣ���¼
}

template <class KeyType, class DataType>
void merge_counting(RecordNode<KeyType, DataType>* origin, RecordNode<KeyType, DataType>* newrec, int low, int m, int high)//����鲢�㷨
{
	int i, j, k;
	i = low; j = m + 1; k = low;
	while ((i <= m) && (j <= high))//�����������ļ��еĵ�һ����¼��ѡ��С�ļ�¼
	{
		++comparing_times; if (origin[i].key <= origin[j].key) { newrec[k] = origin[i]; ++k; ++i; ++moving_times; }
		else { newrec[k] = origin[j]; ++k; ++j; ++moving_times; }
	}
	while (i <= m) { newrec[k] = origin[i]; ++k; ++i; ++moving_times; }//���Ƶ�һ���ļ���ʣ���¼
	while (j <= high) { newrec[k] = origin[j]; ++k; ++j; ++moving_times; }//���Ƶڶ����ļ���ʣ���¼
}

template <class KeyType,class DataType>
void mergePass(RecordNode<KeyType, DataType>* origin, RecordNode<KeyType, DataType>* newrec, int n, int length)//һ�˹鲢�㷨��lengthΪ���˹鲢���������ļ��ĳ���
{
	int i = 0;
	while (i + 2 * length - 1 < n)//����������������ļ�����Ϊlength
	{
		merge(origin, newrec, i, i + length - 1, i + 2 * length - 1);//�鲢����Ϊlength���������ļ�
		i += 2 * length;
	}
	if (i - 1 + length < n - 1)//���ֻʣ���������ļ�������һ������С��length
	{
		merge(origin, newrec, i, i + length - 1, n - 1);
	}
	else
		for (int j = i; j < n; ++j)newrec[j] = origin[j];//�����һ�����ļ����Ƶ�����r1��
}

template <class KeyType, class DataType>
void mergePass_counting(RecordNode<KeyType, DataType>* origin, RecordNode<KeyType, DataType>* newrec, int n, int length)//һ�˹鲢�㷨��lengthΪ���˹鲢���������ļ��ĳ���
{
	int i = 0;
	while (i + 2 * length - 1 < n)//����������������ļ�����Ϊlength
	{
		merge_counting(origin, newrec, i, i + length - 1, i + 2 * length - 1);//�鲢����Ϊlength���������ļ�
		i += 2 * length;
	}
	if (i - 1 + length < n - 1)//���ֻʣ���������ļ�������һ������С��length
	{
		merge_counting(origin, newrec, i, i + length - 1, n - 1);
	}
	else
		for (int j = i; j < n; ++j) { newrec[j] = origin[j]; ++moving_times; }//�����һ�����ļ����Ƶ�����r1��
}



template <class KeyType, class DataType>
struct SortObject
{
	int max;
	int n;//�ļ��еļ�¼����
	RecordNode<KeyType, DataType>* record;
	SortObject(int m = 0)
	{
		max = m; n = 0;
		if (m) { record = new RecordNode<KeyType, DataType>[m]; }
	}
	SortObject(SortObject & a)//���ƹ��캯��
	{
		max = a.max;n = a.n;
		if (max) 
		{
			record = new RecordNode<KeyType, DataType>[max];
			for (int i = 0; i < n; ++i)
			{
				record[i] = a.record[i];
			}
		}
		
	}
	~SortObject()
	{
		delete[]record;
		cout << "Destructor Called" << endl;
	}
	void insertSort()//�����������ֱ�Ӳ�������
	{
		int i, j; RecordNode<KeyType, DataType>tmp;
		for (i = 1; i < n; ++i)
		{
			tmp = record[i];
			for (j = i - 1; (tmp.key < record[j].key) && (j >= 0); --j)
			{
				record[j + 1] = record[j];
			}
			if (j != i - 1) record[j + 1] = tmp; //j=i-1ʱ���ø���
		}
	}
	void insertSort_counting()//�����������ֱ�Ӳ�������
	{
		int i, j; RecordNode<KeyType, DataType>tmp; comparing_times = 0;moving_times = 0;
		for (i = 1; i < n; ++i)
		{
			tmp = record[i]; ++moving_times;
			++comparing_times;//�Ƚϴ���+1�����ٻ�Ƚ�һ�Σ�
			for (j = i - 1; (tmp.key < record[j].key) && (j >= 0); --j)
			{
				record[j + 1] = record[j]; ++moving_times;
				++comparing_times;
			}
			if (j != i - 1) {record[j + 1] = tmp; ++moving_times;} //j=i-1ʱ���ø���
		}
		cout << "�Ƚϴ�����" << comparing_times<<" �ƶ�������"<<moving_times << endl;
	}
	void insertSort_reverse()//�����������ֱ�Ӳ�������
	{
		int i, j; RecordNode<KeyType, DataType>tmp;
		for (i = 1; i < n; ++i)
		{
			tmp = record[i];
			for (j = i - 1; (tmp.key > record[j].key) && (j >= 0); --j)
			{
				record[j + 1] = record[j];
			}
			if (j != i - 1) record[j + 1] = tmp; //j=i-1ʱ���ø���
		}
	}
	void binSort()//����������ж��ַ���������
	{
		int i, j, left, mid, right; RecordNode<KeyType,DataType> tmp; 
		for (i = 1; i < n; ++i)
		{
			tmp = record[i]; left = 0; right = i - 1;
			while (left <= right)
			{
				mid = (left + right) / 2;
				if (tmp.key < record[mid].key)right = mid - 1;
				else left = mid + 1;
			}
			for (j = i - 1; j >= left; --j)
			{
				record[j + 1] = record[j];
			}
			if (left != i)record[left] = tmp;
		}
	}
	void binSort_counting()//����������ж��ַ���������
	{
		int i, j, left, mid, right; RecordNode<KeyType, DataType> tmp; comparing_times = 0; moving_times = 0;
		for (i = 1; i < n; ++i)
		{
			tmp = record[i]; ++moving_times;
			left = 0; right = i - 1;
			while (left <= right)//�ҵ����ʵĲ���λ�á����Ĳ���λ��Ϊleft
			{
				mid = (left + right) / 2;
				++comparing_times; if (tmp.key < record[mid].key)right = mid - 1;
				else left = mid + 1;
			}
			for (j = i - 1; j >= left; --j)//left֮���Ԫ�����������
			{
				record[j + 1] = record[j]; ++moving_times;
			}
			if (left != i) { record[left] = tmp; ++moving_times; }
		}
		cout << "�Ƚϴ�����" << comparing_times << " �ƶ�������" << moving_times << endl;
	}
	void shellSort(int d)//�����������Shell����
	{
		int i, j, inc;
		RecordNode<KeyType, DataType> tmp;
		for (inc = d; inc > 0; inc /= 2)//incΪ��ʱ����
		{
			for (i = inc; i < n; ++i)//ͬʱ��inc����������
			{
				tmp = record[i];//����������¼
				for (j = i - inc; (j >= 0) && (tmp.key < record[j].key); j -= inc)
				{
					record[j + inc] = record[j];//��ļ�¼������
				}
				if (j + inc != i)record[j + inc] = tmp;
			}
		}
	}
	void shellSort_counting(int d)//�����������Shell����
	{
		int i, j, inc; comparing_times = 0; moving_times = 0;
		RecordNode<KeyType, DataType> tmp;
		for (inc = d; inc > 0; inc /= 2)//incΪ��ʱ����
		{
			for (i = inc; i < n; ++i)//ͬʱ��inc����������
			{
				tmp = record[i];//����������¼
				++moving_times;
				++comparing_times;//���ٱȽ�һ��
				for (j = i - inc; (j >= 0) && (tmp.key < record[j].key); j -= inc)
				{
					record[j + inc] = record[j];//��ļ�¼������
					++moving_times;//�����ƶ���һ��
					++comparing_times;//ÿѭ��һ�ֱȽ�һ��
				}
				if (j + inc != i) { record[j + inc] = tmp; ++moving_times; }
			}
		}
		cout << "�Ƚϴ�����" << comparing_times << " �ƶ�������" << moving_times << endl;
	}
	void shellSort_reverse(int d)//�����������Shell����
	{
		int i, j, inc;
		RecordNode<KeyType, DataType> tmp;
		for (inc = d; inc > 0; inc /= 2)//incΪ��ʱ����
		{
			for (i = inc; i < n; ++i)//ͬʱ��inc����������
			{
				tmp = record[i];//����������¼
				for (j = i - inc; (j >= 0) && (tmp.key > record[j].key); j -= inc)
				{
					record[j + inc] = record[j];//��ļ�¼������
				}
				record[j + inc] = tmp;
			}
		}
		//cout << "shellSort Completed!" << endl;
	}
	void selectSort()//�����������ֱ��ѡ������
	{
		int i, j, k;
		RecordNode<KeyType, DataType> tmp;
		for (i = 0; i < n - 1; ++i)//��n-1��ѡ������
		{
			k = i;
			for (j = i + 1; j < n; ++j)
			{
				if (record[j].key < record[k].key)k = j;//����������ҳ���С��
			}
			if (k != i)//�����Ҫ����
			{
				tmp = record[i];
				record[i] = record[k];
				record[k] = tmp;
			}
		}
	}
	void selectSort_counting()//�����������ֱ��ѡ������**�Ƚϴ������ļ���ʼ״̬�޹�
	{
		int i, j, k; comparing_times = 0; moving_times = 0;
		RecordNode<KeyType, DataType> tmp;
		for (i = 0; i < n - 1; ++i)//��n-1��ѡ������
		{
			k = i;
			for (j = i + 1; j < n; ++j)
			{
				++comparing_times;
				if (record[j].key < record[k].key)k = j;//����������ҳ���С��
			}
			if (k != i)//�����Ҫ����
			{
				tmp = record[i];
				record[i] = record[k];
				record[k] = tmp;
				moving_times+=3;
			}
		}
		cout << "�Ƚϴ�����" << comparing_times << " �ƶ�������" << moving_times << endl;
	}
	void bubbleSort()//ð������
	{
		int i, j; bool noswap;
		RecordNode<KeyType, DataType> tmp;
		for (i = 0; i < n - 1; ++i)//��n-1��ð��
		{
			noswap = true;
			for (j = 0; j < n - i-1; ++j)
			{
				if (record[j + 1].key < record[j].key)//�������ı�ǰ���С���ͽ���
				{
					tmp = record[j];
					record[j] = record[j + 1];
					record[j + 1] = tmp;
					noswap = false;
				}
			}
			if (noswap)break;
		}
	}
	void bubbleSort_2()//ð������
	{
		int i, j; bool noswap;
		RecordNode<KeyType, DataType> tmp;
		for (i = 0; i < n/2; ++i)//��n/2��ð��
		{
			noswap = true;
			for (j = i; j < n - 1-i; ++j)//��i��ð�ݵĵ�һ��ʱ����i��֮ǰ���Ѿ��ź���,��n-1-i֮���Ҳ�ź���
			{
				if (record[j + 1].key < record[j].key)
				{
					tmp = record[j];
					record[j] = record[j + 1];
					record[j + 1] = tmp;
					noswap = false;
				}
			}
			if (noswap)break;
			noswap = true;
			for (j = n - 2 - i; j > i; --j)
			{
				if (record[j - 1].key > record[j].key)
				{
					tmp = record[j];
					record[j] = record[j - 1];
					record[j - 1] = tmp;
					noswap = false;
				}
			}
			if (noswap)break;
		}
	}
	void bubbleSort_counting()//ð������
	{
		int i, j; bool noswap; comparing_times = 0; moving_times = 0;
		RecordNode<KeyType, DataType> tmp;
		for (i = 0; i < n - 1; ++i)//��n-1��ð��
		{
			noswap = true;
			for (j = 0; j < n - i-1; ++j)
			{
				++comparing_times; if (record[j + 1].key < record[j].key)
				{
					tmp = record[j];
					record[j] = record[j + 1];
					record[j + 1] = tmp;
					moving_times += 3;
					noswap = false;
				}
			}
			if (noswap)break;
		}
		cout << "�Ƚϴ�����" << comparing_times << " �ƶ�������" << moving_times << endl;
	}
	/*void quickSort_by_Recursion(int l, int r)//���������㷨
	{
		int i, j;
		RecordNode<KeyType, DataType> tmp;
		if (l >= r)return;//ֻ��һ����¼��û�м�¼����������
		i = l; j = r; tmp = record[i];
		while (i != j)
		{
			while ((i < j) && (record[j].key >= tmp.key))--j;//����ɨ����������С��tmp.key�ļ�¼
			if (i < j) { record[i] = record[j]; ++i; }
			while ((i < j) && (record[i].key <= tmp.key))++i;//����ɨ�������������tmp.key�ļ�¼
			if (i < j) { record[j] = record[i]; --j; }
		}
		record[i] = tmp;
		quickSort_by_Recursion(l, i - 1);
		quickSort_by_Recursion(i + 1, r);
	}
	void quickSort() { quickSort_by_Recursion(0, n - 1);}*/
	void mergeSort()//��·�鲢�����㷨
	{
		RecordNode<KeyType, DataType>* newrec = new RecordNode<KeyType, DataType>[n];
		int length = 1;
		while (length < n)
		{
			mergePass(record, newrec, n, length);//һ�˹鲢���������newrec��
			length *= 2;
			mergePass(newrec, record, n, length);//һ�˹鲢���������record�У���֤�����������������record��
			length *= 2;
		}
	}
	void mergeSort_counting()//��·�鲢�����㷨
	{
		RecordNode<KeyType, DataType>* newrec = new RecordNode<KeyType, DataType>[n];
		int length = 1; comparing_times = 0; moving_times = 0;
		while (length < n)
		{
			mergePass_counting(record, newrec, n, length);//һ�˹鲢���������newrec��
			length *= 2;
			mergePass_counting(newrec, record, n, length);//һ�˹鲢���������record�У���֤�����������������record��
			length *= 2;
		}
		cout << "�Ƚϴ�����" << comparing_times << " �ƶ�������" << moving_times << endl;
	}
	friend ostream & operator <<(ostream & os, const SortObject &c)
	{
		for (int i = 0; i < c.n; ++i) { os << c.record[i] << endl; }
		os << endl;
		return os;
	}
	void operator =(const SortObject & c)
	{
		max = c.max; n = c.n;
		for (int i = 0; i < n; ++i)
		{
			record[i] = c.record[i];
		}
	}
};

