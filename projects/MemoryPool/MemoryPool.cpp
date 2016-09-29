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
		//�ѷ��䵽���ڴ滮�ֳ�һϵ��С�飬�������ڲ�������ṹ
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

	//ÿһ�η����ڴ涼�Ǵ�δʹ�õĿ������ͷ����β����һ����

	Unit* pCur = m_UnuseBlockHead;
	
	//�������һ����Է�����ڴ�
	if (pCur->next == nullptr)
	{
		m_UnuseBlockHead = nullptr;
	}
	else
	{
		m_UnuseBlockHead = pCur->next;
	}


	//��ȡ�����ڴ����봦��ʹ��״̬���ڴ��������
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


	//�����û�����ʹ�õ����ݶ�

	return (void*)((char*)pCur + sizeof(Unit));




}

void MemoryPool::DeAlloc(void* p)
{
	//���Ҫ���յ��ڴ治����Դ���ڴ��

	p = (void*)((char*)p - sizeof(Unit));
	if (p < m_pMemory || p >(void*)((char*)m_pMemory + m_ulPoolSize))
	{
		return;
	}

	m_ulAvaliableNumBlocks++;

	Unit* pCur = (Unit*)p;
	//�����ڴ�鲻�����ʱ��ô�򵥣� ��Ϊ���յĿ����λ���ײ���β�������м�
	
	if (pCur->prev == nullptr && pCur->next == nullptr) //�����ʹ���е�һ��
	{
		m_UsedBlockHead = nullptr;
	}
	else if (pCur->prev == nullptr && pCur->next != nullptr) //��һ��
	{
		m_UsedBlockHead = pCur->next;
		m_UsedBlockHead->prev = nullptr;
	}
	else if (pCur->prev != nullptr && pCur->next == nullptr) //���һ��
	{
		pCur->prev->next = nullptr;

	}
	else if (pCur->prev != nullptr && pCur->next != nullptr) //�м�
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




