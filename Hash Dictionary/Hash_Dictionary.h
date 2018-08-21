#ifndef HASH_DICTIONARY_H_INCLUDED
#define HASH_DICTIONARY_H_INCLUDED
#include "DicElement.h"



template <class KeyType, class DataType>
class HashDictionary
{
public:
    int m;//�������򳤶�
    DicElement<KeyType, DataType>* element=NULL;
    HashDictionary (int x=0)//���캯��
    {
        m=x;
        if(m) //�������򳤶Ȳ�Ϊ0
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
    int linearSearch(KeyType k,int* position)//ɢ�б�ļ����㷨����������̽�鷨�����ײ
    {
		int d = hash_function_1(k);
		int c = hash_function_2(k); 
        *position=0;
		int i;
        for (i=0;i<m;++i)
        {
			if ((element[d].key == k) && (!element[d].Deleted)) { *position = d;  return 1; }//�����ɹ�
            else if(element[d].Deleted==true)//�ҵ�һ�����Բ����λ��
            {
                if(!(*position)) *position=d;//�����û�ҵ������ɲ���λ�ã��Ͱѵ�ǰ����Ϊ�ɲ���λ��
            }
            else if (element[d].key==KeyType())//keyΪ��ֵ��ȷ�ϼ���ʧ��
            {
                if(!(*position)) *position=d;//�����û�ҵ������ɲ���λ�ã��Ͱѵ�ǰ����Ϊ�ɲ���λ��
                return 0;
            }
            d=(d+c)%m;
        }
        *position=-1;//ɢ�б����
        return 0;
    }
    int linearInsert(DicElement<KeyType,DataType> ele)
    {
       // if ((element[hash_function(ele.key)].key!=KeyType())&&(element[hash_function(ele.key)].key!=sign))++collision_time;
        int position;
        if(linearSearch(ele.key,&position)==1)//ɢ�б������йؼ���Ϊkey�Ľ��
        {
            cout<<"Find"<<endl;
            return 1;
        }
        else if(position!=-1){element[position]=ele;return 1;}//������
        else return 0;//ɢ�б����
    }
    int linearSearch_and_Print(KeyType k)
    {
        int position;
        if(linearSearch(k,&position)==1){cout<<element[position];return 1;}
        else{cout<<"Not Exist!"<<endl;return 0;}
    }
    int linearDelete(KeyType k)//ɾ��ĳ���
    {
        int position;
        if(linearSearch(k,&position)==1)//����ҵ���
        {
			element[position].Deleted = true;//key�����
            cout<<"Deleted!"<<endl;
            return 1;
        }
        else{cout<<"Not Exist!"<<endl;return 0;}
    }

};



#endif // HASH_DICTIONARY_H_INCLUDED
