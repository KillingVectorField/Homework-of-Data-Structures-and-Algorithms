#ifndef DICELEMENT_H_INCLUDED
#define DICELEMENT_H_INCLUDED
#include <iostream>
#include<string>
#define keyname "�ؼ��֣�"
#define valuename "���ݣ�"
using namespace std;
template <class KeyType, class DataType>
struct DicElement
{
public:
     KeyType key;//�ؼ����ֶ�
     DataType value;//�����ֶ�
	 bool Deleted = false;
     DicElement(KeyType k=KeyType(),DataType v=DataType()):key(k),value(v){}
	 friend ostream & operator <<(ostream & os, const DicElement &c)
	 {
		 os << keyname << c.key << " " << valuename << c.value << endl;
		 return os;
	 }
};

#endif // DICELEMENT_H_INCLUDED
