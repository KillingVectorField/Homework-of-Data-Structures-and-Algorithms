#ifndef DICELEMENT_H_INCLUDED
#define DICELEMENT_H_INCLUDED
#include <iostream>
#include<string>
#define keyname "¹Ø¼ü×Ö£º"
#define valuename "ÄÚÈÝ£º"
using namespace std;
template <class KeyType, class DataType>
struct DicElement
{
public:
     KeyType key;//¹Ø¼üÂë×Ö¶Î
     DataType value;//ÊôÐÔ×Ö¶Î
	 bool Deleted = false;
     DicElement(KeyType k=KeyType(),DataType v=DataType()):key(k),value(v){}
	 friend ostream & operator <<(ostream & os, const DicElement &c)
	 {
		 os << keyname << c.key << " " << valuename << c.value << endl;
		 return os;
	 }
};

#endif // DICELEMENT_H_INCLUDED
