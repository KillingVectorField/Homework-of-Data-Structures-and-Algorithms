#pragma once
#include <iostream>
using namespace std;
#define keyname "关键字："
#define infoname "内容："

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
void merge(RecordNode<KeyType, DataType>* origin, RecordNode<KeyType, DataType>* newrec, int low, int m,int high)//两组归并算法
{
	int i, j, k;
	i = low; j = m + 1; k = low;
	while ((i <= m) && (j <= high))//从两个有序文件中的第一个记录中选出小的记录
	{
		if(origin[i].key <= origin[j].key){newrec[k] = origin[i]; ++k; ++i; }
		else { newrec[k] = origin[j]; ++k; ++j; }
	}
	while (i <= m) { newrec[k] = origin[i]; ++k; ++i; }//复制第一个文件的剩余记录
	while (j <= high) { newrec[k] = origin[j]; ++k; ++j; }//复制第二个文件的剩余记录
}

template <class KeyType, class DataType>
void merge_counting(RecordNode<KeyType, DataType>* origin, RecordNode<KeyType, DataType>* newrec, int low, int m, int high)//两组归并算法
{
	int i, j, k;
	i = low; j = m + 1; k = low;
	while ((i <= m) && (j <= high))//从两个有序文件中的第一个记录中选出小的记录
	{
		++comparing_times; if (origin[i].key <= origin[j].key) { newrec[k] = origin[i]; ++k; ++i; ++moving_times; }
		else { newrec[k] = origin[j]; ++k; ++j; ++moving_times; }
	}
	while (i <= m) { newrec[k] = origin[i]; ++k; ++i; ++moving_times; }//复制第一个文件的剩余记录
	while (j <= high) { newrec[k] = origin[j]; ++k; ++j; ++moving_times; }//复制第二个文件的剩余记录
}

template <class KeyType,class DataType>
void mergePass(RecordNode<KeyType, DataType>* origin, RecordNode<KeyType, DataType>* newrec, int n, int length)//一趟归并算法，length为本趟归并的有序子文件的长度
{
	int i = 0;
	while (i + 2 * length - 1 < n)//如果至少有两个子文件长度为length
	{
		merge(origin, newrec, i, i + length - 1, i + 2 * length - 1);//归并长度为length的两个子文件
		i += 2 * length;
	}
	if (i - 1 + length < n - 1)//如果只剩下两个子文件，其中一个长度小于length
	{
		merge(origin, newrec, i, i + length - 1, n - 1);
	}
	else
		for (int j = i; j < n; ++j)newrec[j] = origin[j];//将最后一个子文件复制到数组r1中
}

template <class KeyType, class DataType>
void mergePass_counting(RecordNode<KeyType, DataType>* origin, RecordNode<KeyType, DataType>* newrec, int n, int length)//一趟归并算法，length为本趟归并的有序子文件的长度
{
	int i = 0;
	while (i + 2 * length - 1 < n)//如果至少有两个子文件长度为length
	{
		merge_counting(origin, newrec, i, i + length - 1, i + 2 * length - 1);//归并长度为length的两个子文件
		i += 2 * length;
	}
	if (i - 1 + length < n - 1)//如果只剩下两个子文件，其中一个长度小于length
	{
		merge_counting(origin, newrec, i, i + length - 1, n - 1);
	}
	else
		for (int j = i; j < n; ++j) { newrec[j] = origin[j]; ++moving_times; }//将最后一个子文件复制到数组r1中
}



template <class KeyType, class DataType>
struct SortObject
{
	int max;
	int n;//文件中的记录个数
	RecordNode<KeyType, DataType>* record;
	SortObject(int m = 0)
	{
		max = m; n = 0;
		if (m) { record = new RecordNode<KeyType, DataType>[m]; }
	}
	SortObject(SortObject & a)//复制构造函数
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
	void insertSort()//按递增序进行直接插入排序
	{
		int i, j; RecordNode<KeyType, DataType>tmp;
		for (i = 1; i < n; ++i)
		{
			tmp = record[i];
			for (j = i - 1; (tmp.key < record[j].key) && (j >= 0); --j)
			{
				record[j + 1] = record[j];
			}
			if (j != i - 1) record[j + 1] = tmp; //j=i-1时不用复制
		}
	}
	void insertSort_counting()//按递增序进行直接插入排序
	{
		int i, j; RecordNode<KeyType, DataType>tmp; comparing_times = 0;moving_times = 0;
		for (i = 1; i < n; ++i)
		{
			tmp = record[i]; ++moving_times;
			++comparing_times;//比较次数+1（至少会比较一次）
			for (j = i - 1; (tmp.key < record[j].key) && (j >= 0); --j)
			{
				record[j + 1] = record[j]; ++moving_times;
				++comparing_times;
			}
			if (j != i - 1) {record[j + 1] = tmp; ++moving_times;} //j=i-1时不用复制
		}
		cout << "比较次数：" << comparing_times<<" 移动次数："<<moving_times << endl;
	}
	void insertSort_reverse()//按递增序进行直接插入排序
	{
		int i, j; RecordNode<KeyType, DataType>tmp;
		for (i = 1; i < n; ++i)
		{
			tmp = record[i];
			for (j = i - 1; (tmp.key > record[j].key) && (j >= 0); --j)
			{
				record[j + 1] = record[j];
			}
			if (j != i - 1) record[j + 1] = tmp; //j=i-1时不用复制
		}
	}
	void binSort()//按递增序进行二分法插入排序
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
	void binSort_counting()//按递增序进行二分法插入排序
	{
		int i, j, left, mid, right; RecordNode<KeyType, DataType> tmp; comparing_times = 0; moving_times = 0;
		for (i = 1; i < n; ++i)
		{
			tmp = record[i]; ++moving_times;
			left = 0; right = i - 1;
			while (left <= right)//找到合适的插入位置。最后的插入位置为left
			{
				mid = (left + right) / 2;
				++comparing_times; if (tmp.key < record[mid].key)right = mid - 1;
				else left = mid + 1;
			}
			for (j = i - 1; j >= left; --j)//left之后的元素依次向后移
			{
				record[j + 1] = record[j]; ++moving_times;
			}
			if (left != i) { record[left] = tmp; ++moving_times; }
		}
		cout << "比较次数：" << comparing_times << " 移动次数：" << moving_times << endl;
	}
	void shellSort(int d)//按递增序进行Shell排序
	{
		int i, j, inc;
		RecordNode<KeyType, DataType> tmp;
		for (inc = d; inc > 0; inc /= 2)//inc为当时增量
		{
			for (i = inc; i < n; ++i)//同时做inc个序列排序
			{
				tmp = record[i];//保存待插入记录
				for (j = i - inc; (j >= 0) && (tmp.key < record[j].key); j -= inc)
				{
					record[j + inc] = record[j];//大的记录往后移
				}
				if (j + inc != i)record[j + inc] = tmp;
			}
		}
	}
	void shellSort_counting(int d)//按递增序进行Shell排序
	{
		int i, j, inc; comparing_times = 0; moving_times = 0;
		RecordNode<KeyType, DataType> tmp;
		for (inc = d; inc > 0; inc /= 2)//inc为当时增量
		{
			for (i = inc; i < n; ++i)//同时做inc个序列排序
			{
				tmp = record[i];//保存待插入记录
				++moving_times;
				++comparing_times;//至少比较一次
				for (j = i - inc; (j >= 0) && (tmp.key < record[j].key); j -= inc)
				{
					record[j + inc] = record[j];//大的记录往后移
					++moving_times;//这里移动了一次
					++comparing_times;//每循环一轮比较一次
				}
				if (j + inc != i) { record[j + inc] = tmp; ++moving_times; }
			}
		}
		cout << "比较次数：" << comparing_times << " 移动次数：" << moving_times << endl;
	}
	void shellSort_reverse(int d)//按递增序进行Shell排序
	{
		int i, j, inc;
		RecordNode<KeyType, DataType> tmp;
		for (inc = d; inc > 0; inc /= 2)//inc为当时增量
		{
			for (i = inc; i < n; ++i)//同时做inc个序列排序
			{
				tmp = record[i];//保存待插入记录
				for (j = i - inc; (j >= 0) && (tmp.key > record[j].key); j -= inc)
				{
					record[j + inc] = record[j];//大的记录往后移
				}
				record[j + inc] = tmp;
			}
		}
		//cout << "shellSort Completed!" << endl;
	}
	void selectSort()//按递增序进行直接选择排序
	{
		int i, j, k;
		RecordNode<KeyType, DataType> tmp;
		for (i = 0; i < n - 1; ++i)//做n-1趟选择排序
		{
			k = i;
			for (j = i + 1; j < n; ++j)
			{
				if (record[j].key < record[k].key)k = j;//在无序段中找出最小的
			}
			if (k != i)//如果需要交换
			{
				tmp = record[i];
				record[i] = record[k];
				record[k] = tmp;
			}
		}
	}
	void selectSort_counting()//按递增序进行直接选择排序**比较次数与文件初始状态无关
	{
		int i, j, k; comparing_times = 0; moving_times = 0;
		RecordNode<KeyType, DataType> tmp;
		for (i = 0; i < n - 1; ++i)//做n-1趟选择排序
		{
			k = i;
			for (j = i + 1; j < n; ++j)
			{
				++comparing_times;
				if (record[j].key < record[k].key)k = j;//在无序段中找出最小的
			}
			if (k != i)//如果需要交换
			{
				tmp = record[i];
				record[i] = record[k];
				record[k] = tmp;
				moving_times+=3;
			}
		}
		cout << "比较次数：" << comparing_times << " 移动次数：" << moving_times << endl;
	}
	void bubbleSort()//冒泡排序
	{
		int i, j; bool noswap;
		RecordNode<KeyType, DataType> tmp;
		for (i = 0; i < n - 1; ++i)//做n-1次冒泡
		{
			noswap = true;
			for (j = 0; j < n - i-1; ++j)
			{
				if (record[j + 1].key < record[j].key)//如果后面的比前面的小，就交换
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
	void bubbleSort_2()//冒泡排序
	{
		int i, j; bool noswap;
		RecordNode<KeyType, DataType> tmp;
		for (i = 0; i < n/2; ++i)//做n/2次冒泡
		{
			noswap = true;
			for (j = i; j < n - 1-i; ++j)//第i次冒泡的第一趟时，第i个之前的已经排好了,第n-1-i之后的也排好了
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
	void bubbleSort_counting()//冒泡排序
	{
		int i, j; bool noswap; comparing_times = 0; moving_times = 0;
		RecordNode<KeyType, DataType> tmp;
		for (i = 0; i < n - 1; ++i)//做n-1次冒泡
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
		cout << "比较次数：" << comparing_times << " 移动次数：" << moving_times << endl;
	}
	/*void quickSort_by_Recursion(int l, int r)//快速排序算法
	{
		int i, j;
		RecordNode<KeyType, DataType> tmp;
		if (l >= r)return;//只有一个记录或没有记录，无需排序
		i = l; j = r; tmp = record[i];
		while (i != j)
		{
			while ((i < j) && (record[j].key >= tmp.key))--j;//向左扫描找排序码小于tmp.key的记录
			if (i < j) { record[i] = record[j]; ++i; }
			while ((i < j) && (record[i].key <= tmp.key))++i;//向右扫描找排序码大于tmp.key的记录
			if (i < j) { record[j] = record[i]; --j; }
		}
		record[i] = tmp;
		quickSort_by_Recursion(l, i - 1);
		quickSort_by_Recursion(i + 1, r);
	}
	void quickSort() { quickSort_by_Recursion(0, n - 1);}*/
	void mergeSort()//二路归并排序算法
	{
		RecordNode<KeyType, DataType>* newrec = new RecordNode<KeyType, DataType>[n];
		int length = 1;
		while (length < n)
		{
			mergePass(record, newrec, n, length);//一趟归并，结果放在newrec中
			length *= 2;
			mergePass(newrec, record, n, length);//一趟归并，结果放在record中，保证最后的排序结果还存放在record中
			length *= 2;
		}
	}
	void mergeSort_counting()//二路归并排序算法
	{
		RecordNode<KeyType, DataType>* newrec = new RecordNode<KeyType, DataType>[n];
		int length = 1; comparing_times = 0; moving_times = 0;
		while (length < n)
		{
			mergePass_counting(record, newrec, n, length);//一趟归并，结果放在newrec中
			length *= 2;
			mergePass_counting(newrec, record, n, length);//一趟归并，结果放在record中，保证最后的排序结果还存放在record中
			length *= 2;
		}
		cout << "比较次数：" << comparing_times << " 移动次数：" << moving_times << endl;
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

