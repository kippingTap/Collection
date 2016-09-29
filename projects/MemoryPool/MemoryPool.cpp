#include"MemoryPool.h"

#include"malloc.h"

#ifdef _DEBUGPOOL

#include<iostream>
using namespace std;

#endif // _DEBUGPOOL


MemoryPool::MemoryPool(unsigned long ulBlockSize, unsigned long ulNumBlocks):m_ulBlockSize(ulBlockSize),m_ulNumBlocks(ulNumBlocks),m_ulAvaliableNumBlocks(m_ulNumBlocks),m_UnuseBlockHead(),m_UsedBlockHead()
{

	unsigned long actullBlockSize = m_ulBlockSize + sizeof(Unit);
	m_ulPoolSize = m_ulNumBlocks * actullBlockSize;
	
	m_pMemory = malloc(m_ulPoolSize);

	if (m_pMemory != nullptr)
	{
		//把分配到的内存划分成一系列小块，并建立内部的链表结构
		for (long i = m_ulNumBlocks - 1; i >= 0; i--)
		{
			Unit* pCur = (Unit*)((char*)m_pMemory + i * actullBlockSize);

			pCur->prev = nullptr;
			if (m_UnuseBlockHead != nullptr)
			{
				pCur->next = m_UnuseBlockHead;
				m_UnuseBlockHead->prev = pCur;
				m_UnuseBlockHead = pCur;
			}
			else
			{
				pCur->next = nullptr;
				m_UnuseBlockHead = pCur;
			}
		}
	}
}


MemoryPool::~MemoryPool()
{
	if (m_pMemory)
	{
		delete m_pMemory;
		m_pMemory = nullptr;
	}
}

void* MemoryPool::Alloc(size_t size)
{
	if (m_pMemory == nullptr || m_UnuseBlockHead == nullptr || size > m_ulBlockSize)
	{
		return  nullptr;
	}

	m_ulAvaliableNumBlocks--;

	//每一次分配内存都是从未使用的块链表的头部向尾部逐一分配

	Unit* pCur = m_UnuseBlockHead;
	
	//这是最后一块可以分配的内存
	if (pCur->next == nullptr)
	{
		m_UnuseBlockHead = nullptr;
	}
	else
	{
		m_UnuseBlockHead = pCur->next;
	}


	//把取出的内存块加入处于使用状态的内存块链表中
	pCur->prev = nullptr;
	if(m_UsedBlockHead != nullptr)
	{ 
		pCur->next = m_UsedBlockHead;
		m_UsedBlockHead->prev = pCur;
		m_UsedBlockHead = pCur;
	}
	else
	{
		pCur->next = nullptr;
		m_UsedBlockHead = pCur;
	}


#ifdef _DEBUGPOOL

	cout << "Alloc form pool.." << endl;

#endif // _DEBUGPOOL


	//返回用户可以使用的数据段

	return (void*)((char*)pCur + sizeof(Unit));




}

void MemoryPool::DeAlloc(void* p)
{
	//如果要回收的内存不是来源于内存池

	p = (void*)((char*)p - sizeof(Unit));
	if (p < m_pMemory || p >(void*)((char*)m_pMemory + m_ulPoolSize))
	{
		return;
	}

	m_ulAvaliableNumBlocks++;

	Unit* pCur = (Unit*)p;
	//回收内存块不像分配时那么简单， 因为回收的块可能位于首部，尾部或者中间
	
	if (pCur->prev == nullptr && pCur->next == nullptr) //最后处于使用中的一块
	{
		m_UsedBlockHead = nullptr;
	}
	else if (pCur->prev == nullptr && pCur->next != nullptr) //第一块
	{
		m_UsedBlockHead = pCur->next;
		m_UsedBlockHead->prev = nullptr;
	}
	else if (pCur->prev != nullptr && pCur->next == nullptr) //最后一块
	{
		pCur->prev->next = nullptr;

	}
	else if (pCur->prev != nullptr && pCur->next != nullptr) //中间
	{
		pCur->prev->next = pCur->next;
		pCur->next->prev = pCur->prev;

	}

	pCur->prev = nullptr;

	if (m_UnuseBlockHead == nullptr)
	{
		pCur->next = nullptr;
		m_UnuseBlockHead = pCur;
	}
	else
	{
		pCur->next = m_UnuseBlockHead;
		m_UnuseBlockHead->prev = pCur;
	}
	
	m_UnuseBlockHead = pCur;

#ifdef _DEBUGPOOL

	cout << "deAlloc form pool.." << endl;

#endif // _DEBUGPOOL
	
}




