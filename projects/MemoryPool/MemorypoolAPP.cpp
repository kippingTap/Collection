#include"MemoryPool.h"
#include<iostream>
using namespace std;

int main()
{
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



	system("PAUSE");
	return 0;
}