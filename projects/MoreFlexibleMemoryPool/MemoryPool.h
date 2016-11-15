#pragma once
#include<string>
#include<Windows.h>

// a more flexible and extensible memory pool
// if the pool memory is running out. it can dynamicly grow if you set the m_Allow2GrowMemPool = true
//do some test text

class MemoryPool
{
private:
	unsigned char** m_ppRawMemArray;  // memory blocks
	rsize_t m_numBlocksInMemArray;

	unsigned char* m_pHead;
	size_t m_chunkSize;  // per block
 	size_t m_NumChunks;  // per block
	bool m_Allow2GrowMemPool;


#ifdef _DEBUG
private:
	size_t m_allocSize;  // current alloc chunk size
	size_t m_alloBottleneck;  //max alloc chunk size during the lift time

	std::string m_PoolName;

public:
	void DebugOutputMemoryPoolUseInfo()
	{
		std::string useInfo = "\n\n";
		useInfo += "MemoryPool [";
		useInfo += DebugGetPoolName();
		useInfo += "] use info -----------------------------------------------------------------------------------------------------------\n";
		useInfo += "total chunk: ";
		useInfo += std::to_string(m_NumChunks * m_numBlocksInMemArray);
		useInfo += "\n";
		useInfo += "used chunk: ";
		useInfo += std::to_string(m_allocSize);
		useInfo += "\n";
		useInfo += "use bottleneck: ";
		useInfo += std::to_string(m_alloBottleneck);
		useInfo += "\n";
		useInfo += "use ratio: ";
		useInfo += std::to_string((float)m_allocSize / (float)(m_NumChunks * m_numBlocksInMemArray));
		useInfo += "\n";
		useInfo += "MemoryPool [";
		useInfo += DebugGetPoolName();
		useInfo += "] use info -----------------------------------------------------------------------------------------------------------\n";
		OutputDebugStringA(useInfo.c_str());
	}
#endif // _DEBUG


public:

	MemoryPool(size_t chunkSize, size_t numChunks);
	~MemoryPool();
	bool Init();
	void* Alloc();
	void Free(void* pChunck);
	void Destory();

	bool SetAllow2GrowMemPool(bool allow2GrowMemPool)
	{
		m_Allow2GrowMemPool = allow2GrowMemPool;
	}

	bool GetAllow2GrowMemPool()const
	{
		return m_Allow2GrowMemPool;
	}

#ifdef _DEBUG

	size_t DebugGetAllocSize()const
	{
		return m_allocSize;
	}

	size_t DebugGetAllocBottlenect()const
	{
		return m_alloBottleneck;
	}

	void DebugSetPoolName(const std::string& name)
	{
		m_PoolName = name;
	}

	std::string DebugGetPoolName()const
	{
		return m_PoolName;
	}

#endif // _DEBUG


private:
	// inner helper 

	
	void Reset();

	bool GrowMemoryPool();

	unsigned char* CreateNewMemoryBlock();

	void SetNext(unsigned char* pCurChunk, unsigned char* pNextChunk);
	unsigned char* GetNext(unsigned char* pCurChunk);

	void DebugOutPutOutOfMemoryError();


	//can't copy and assigment
	MemoryPool(const MemoryPool& rhs){}
	MemoryPool& operator = (const MemoryPool& rhs){}
};
