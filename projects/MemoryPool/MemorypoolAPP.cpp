#include"MemoryPool.h"
#include<iostream>
#include<cassert>
#include<Windows.h>
#include"TestClass1.h"
#include"TestClass2.h"
using namespace std;


MemoryPool* g_pMemoryPool = nullptr;

#define TEST_COUNT 10000000

int main()
{

	g_pMemoryPool = new MemoryPool(sizeof(TestClass1), 1024);

	assert(g_pMemoryPool != nullptr);


	
	DWORD dwBeg = GetTickCount();

	for (int i = 0; i < TEST_COUNT; ++i)
	{
		TestClass1* p = new TestClass1;    // form memorypool
		if (p)
			delete p; 
	}

	DWORD dwEnd = GetTickCount();
	cout << "Alloc memory form pool total interval: " << dwEnd - dwBeg << " ms" << endl;

	dwBeg = GetTickCount();

	for (int i = 0; i < TEST_COUNT; ++i)
	{
		TestClass2* p = new TestClass2;    // form heap
		if (p)
			delete p;
	}

	dwEnd = GetTickCount();
	cout << "Alloc memory form heap total interval: " << dwEnd - dwBeg << " ms" << endl;

	/*
	MemoryPool* pMempool = new MemoryPool(sizeof(double),10);
	if (pMempool)
	{
		cout << "--------------------------------Memory pool info--------------------------------" << endl;
		cout << " block size       tatal block       avaliable block         " << endl;
		cout << pMempool->GetBlockSize() << "              " << pMempool->GetBlockCount() << "              " << pMempool->GetAvaliableBlockCount() << endl;
		cout << "--------------------------------Memory pool info--------------------------------" << endl;
		cout << endl << endl;

		double* pmyDouble = (double*)pMempool->Alloc(sizeof(double));
		if (pmyDouble)
		{
			*pmyDouble = 3.14159;
			cout << "alloc a double : " << *pmyDouble << endl;
			cout << "--------------------------------Memory pool info--------------------------------" << endl;
			cout << " block size       tatal block       avaliable block         " << endl;
			cout << pMempool->GetBlockSize() << "              " << pMempool->GetBlockCount() << "              " << pMempool->GetAvaliableBlockCount() << endl;
			cout << "--------------------------------Memory pool info--------------------------------" << endl;
			cout << endl << endl;

		}

		int* ppmyIntArray[10];

		for (int i = 0; i < 10; ++i)
		{
			int* pmyInt = (int*)pMempool->Alloc(sizeof(int));
			
			if (pmyInt)
			{
				*pmyInt = i*100 + i;

				ppmyIntArray[i] = pmyInt;

				cout << "alloc a int : " << *pmyInt << endl;
				cout << "--------------------------------Memory pool info--------------------------------" << endl;
				cout << " block size       tatal block       avaliable block         " << endl;
				cout << pMempool->GetBlockSize() << "              " << pMempool->GetBlockCount() << "              " << pMempool->GetAvaliableBlockCount() << endl;
				cout << "--------------------------------Memory pool info--------------------------------" << endl;
				cout << endl << endl;

			}
			else
			{
				cout << "out of memory!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
				ppmyIntArray[i] = nullptr;
			}

		}
	

		cout << endl << endl;

		for(int i =0; i< 10; ++i) 
		{
			if (ppmyIntArray[i])
			{

				pMempool->DeAlloc((void*)ppmyIntArray[i]);
				cout << "dealloc a int:   " << *ppmyIntArray[i]<<endl;
				cout << "--------------------------------Memory pool info--------------------------------" << endl;
				cout << " block size       tatal block       avaliable block         " << endl;
				cout << pMempool->GetBlockSize() << "              " << pMempool->GetBlockCount() << "              " << pMempool->GetAvaliableBlockCount() << endl;
				cout << "--------------------------------Memory pool info--------------------------------" << endl;
				cout << endl << endl;

			}
	

		}



		if (pmyDouble)
		{

			pMempool->DeAlloc((void*)pmyDouble);
			cout << "dealloc a double..." << endl;
			cout << "--------------------------------Memory pool info----------------------------------" << endl;
			cout << " block size          tatal block          avaliable block          pool size" << endl;
			cout << pMempool->GetBlockSize() << "              " << pMempool->GetBlockCount() << "              " << pMempool->GetAvaliableBlockCount() << endl;
			cout << "--------------------------------Memory pool info----------------------------------" << endl;
			cout << endl << endl;

		}






		for (int i = 0; i < 10; ++i)
		{
			int* pmyInt = (int*)pMempool->Alloc(sizeof(int));

			if (pmyInt)
			{
				*pmyInt = i * 100 + i;

				ppmyIntArray[i] = pmyInt;

				cout << "alloc a int : " << *pmyInt << endl;
				cout << "--------------------------------Memory pool info--------------------------------" << endl;
				cout << " block size       tatal block       avaliable block         " << endl;
				cout << pMempool->GetBlockSize() << "              " << pMempool->GetBlockCount() << "              " << pMempool->GetAvaliableBlockCount() << endl;
				cout << "--------------------------------Memory pool info--------------------------------" << endl;
				cout << endl << endl;

			}
			else
			{
				cout << "out of memory!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
				ppmyIntArray[i] = nullptr;
			}

		}


		cout << endl << endl;

		for (int i = 0; i< 10; ++i)
		{
			if (ppmyIntArray[i])
			{

				pMempool->DeAlloc((void*)ppmyIntArray[i]);
				cout << "dealloc a int:   " << *ppmyIntArray[i] << endl;
				cout << "--------------------------------Memory pool info--------------------------------" << endl;
				cout << " block size       tatal block       avaliable block         " << endl;
				cout << pMempool->GetBlockSize() << "              " << pMempool->GetBlockCount() << "              " << pMempool->GetAvaliableBlockCount() << endl;
				cout << "--------------------------------Memory pool info--------------------------------" << endl;
				cout << endl << endl;

			}


		}




		delete pMempool;
	}

	*/



	system("PAUSE");
	return 0;
}