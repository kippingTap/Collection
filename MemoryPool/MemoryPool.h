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
	void* m_pMemory;    //指向该内存池一大块内存的指针
	unsigned long m_ulBlockSize;  //内存池被分成一系列小块内存作为分配和回收单元，这里指定每一小块单元的大小(byte)
	unsigned long m_ulNumBlocks; //整个内存池被分成小块的总块数
	unsigned long m_ulPoolSize;
	unsigned long m_ulAvaliableNumBlocks;

	Unit* m_UsedBlockHead;
	Unit* m_UnuseBlockHead;   //管理内存池分配和回收的两个链表

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

