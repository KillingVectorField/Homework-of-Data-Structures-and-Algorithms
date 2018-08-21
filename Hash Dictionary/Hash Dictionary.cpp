// Hash Dictionary.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "DicElement.h"
#include "Hash_Dictionary.h"


int main()
{
	HashDictionary<int, int>* Dic = new HashDictionary<int, int>(7);
	for (int i = 0; i < 5; ++i)
	{
		Dic->linearInsert(DicElement<int, int>(100+i, 100+i));
	}
	cout << Dic->element[6]<<endl;
	Dic->linearDelete(104);
	Dic->linearDelete(104);/*
	Dic->linearSearch_and_Print(104);
	Dic->linearInsert(DicElement<int, int>(104, 102));
	Dic->linearSearch_and_Print(104);
	cout << Dic->element[6] << endl;*/
    return 0;
}

