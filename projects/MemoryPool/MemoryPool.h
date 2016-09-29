#ifndef  Memory_Pool_H
#define Memory_Pool_H


class MemoryPool
{
	struct Unit
	{
		Unit* prev;
		Unit* next;
		Unit():prev(nullptr),next(nullptr){}
	};
private:
	void* m_pMemory;    //ָ����ڴ��һ����ڴ��ָ��
	unsigned long m_ulBlockSize;  //�ڴ�ر��ֳ�һϵ��С���ڴ���Ϊ����ͻ��յ�Ԫ������ָ��ÿһС�鵥Ԫ�Ĵ�С(byte)
	unsigned long m_ulNumBlocks; //�����ڴ�ر��ֳ�С����ܿ���
	unsigned long m_ulPoolSize;
	unsigned long m_ulAvaliableNumBlocks;

	Unit* m_UsedBlockHead;
	Unit* m_UnuseBlockHead;   //�����ڴ�ط���ͻ��յ���������

public:
	MemoryPool(unsigned long ulBlockSize, unsigned long ulNumBlocks);
	~MemoryPool();

	void* Alloc(size_t size);

	void DeAlloc(void* p);

	unsigned long GetBlockSize()const
	{
		
		return	m_pMemory == nullptr ? 0 : m_ulBlockSize;
		
	}

	unsigned long GetBlockCount()const
	{
		return	m_pMemory == nullptr ? 0 : m_ulNumBlocks;
	}

	unsigned long GetAvaliableBlockCount() const
	{
		return	m_pMemory == nullptr ? 0 : m_ulAvaliableNumBlocks;
	}

};

#endif // ! Memory_Pool_H

