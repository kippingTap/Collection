#include<Windows.h>
#include"MemoryPool.h"
#include<iostream>
using namespace std;






int main()
{
	MemoryPool* myMemoryPool = new MemoryPool(128,10);

	if (myMemoryPool)
	{
#ifdef _DEBUG
		myMemoryPool->DebugSetPoolName("memoryPool_128");
#endif // _DEBUG
		if(!myMemoryPool->Init())
		{
#ifdef _DEBUG
			cout << myMemoryPool->DebugGetPoolName();
#endif // _DEBUG
			cout << " fail to init!" << endl;
			exit(1);
		}

		int* pInt = (int*)myMemoryPool->Alloc();
		if (pInt)
		{
			*pInt = 7788;
			cout << "Int: " << *pInt << endl;
		}
		

		char* pChar = (char*)myMemoryPool->Alloc();
		if (pChar)
		{
			*pChar = 'A';
			cout << "Charater: " << *pChar << endl;
		}

		float* pFloat = (float*)myMemoryPool->Alloc();
		if (pFloat)
		{
			*pFloat = 3.14159;
			cout << "Float: " << *pFloat << endl;
		}

#ifdef _DEBUG
		myMemoryPool->DebugOutputMemoryPoolUseInfo();
#endif // _DEBUG


		myMemoryPool->Free(pFloat);

#ifdef _DEBUG
		myMemoryPool->DebugOutputMemoryPoolUseInfo();
#endif // _DEBUG

		myMemoryPool->Destory();

#ifdef _DEBUG
		myMemoryPool->DebugOutputMemoryPoolUseInfo();
#endif // _DEBUG

	}

	system("PAUSE");
	return 0;
}