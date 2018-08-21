#ifndef HASH_DICTIONARY_H_INCLUDED
#define HASH_DICTIONARY_H_INCLUDED
#include "DicElement.h"



template <class KeyType, class DataType>
class HashDictionary
{
public:
    int m;//基本区域长度
    DicElement<KeyType, DataType>* element=NULL;
    HashDictionary (int x=0)//构造函数
    {
        m=x;
        if(m) //基本区域长度不为0
        {
            element=new DicElement<KeyType, DataType>[m];
        }
    }
	int hash_function_1(KeyType key)
	{
		return key%m;
	}
	int hash_function_2(KeyType key)
	{
		return key % (m - 2) + 1;
	}
    int linearSearch(KeyType k,int* position)//散列表的检索算法——用线性探查法解决碰撞
    {
		int d = hash_function_1(k);
		int c = hash_function_2(k); 
        *position=0;
		int i;
        for (i=0;i<m;++i)
        {
			if ((element[d].key == k) && (!element[d].Deleted)) { *position = d;  return 1; }//检索成功
            else if(element[d].Deleted==true)//找到一个可以插入的位置
            {
                if(!(*position)) *position=d;//如果还没找到过个可插入位置，就把当前点设为可插入位置
            }
            else if (element[d].key==KeyType())//key为零值，确认检索失败
            {
                if(!(*position)) *position=d;//如果还没找到过个可插入位置，就把当前点设为可插入位置
                return 0;
            }
            d=(d+c)%m;
        }
        *position=-1;//散列表溢出
        return 0;
    }
    int linearInsert(DicElement<KeyType,DataType> ele)
    {
       // if ((element[hash_function(ele.key)].key!=KeyType())&&(element[hash_function(ele.key)].key!=sign))++collision_time;
        int position;
        if(linearSearch(ele.key,&position)==1)//散列表中已有关键码为key的结点
        {
            cout<<"Find"<<endl;
            return 1;
        }
        else if(position!=-1){element[position]=ele;return 1;}//插入结点
        else return 0;//散列表溢出
    }
    int linearSearch_and_Print(KeyType k)
    {
        int position;
        if(linearSearch(k,&position)==1){cout<<element[position];return 1;}
        else{cout<<"Not Exist!"<<endl;return 0;}
    }
    int linearDelete(KeyType k)//删除某结点
    {
        int position;
        if(linearSearch(k,&position)==1)//如果找到了
        {
			element[position].Deleted = true;//key做标记
            cout<<"Deleted!"<<endl;
            return 1;
        }
        else{cout<<"Not Exist!"<<endl;return 0;}
    }

};



#endif // HASH_DICTIONARY_H_INCLUDED
