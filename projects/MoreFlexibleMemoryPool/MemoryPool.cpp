#include"MemoryPool.h"
#include<cstdlib>


#define CHUNK_HEAD_SIZE sizeof(unsigned char*)

MemoryPool::MemoryPool(size_t chunkSize, size_t numChunks)
{
	Reset();
	m_chunkSize = chunkSize;
	m_NumChunks = numChunks;
}

MemoryPool::~MemoryPool()
{
	if (m_ppRawMemArray)
	{
		Destory();
	}
}


bool MemoryPool::Init()
{

	if (m_ppRawMemArray)
	{
		Destory();
	}

	if (!GrowMemoryPool())
	{
		return false;
	}
	return true;
}

void* MemoryPool::Alloc()
{
	if (m_pHead == nullptr) // the pool is running out
	{
		if (m_Allow2GrowMemPool)
		{
			if (!GrowMemoryPool())
				return nullptr;
		}
		else
		{
			return nullptr;
		}
	}

	unsigned char* pRet = m_pHead;
	unsigned char* pnext = GetNext(m_pHead);
	m_pHead = pnext;

#ifdef _DEBUG
	++m_allocSize;
	if (m_alloBottleneck < m_allocSize)
		m_alloBottleneck = m_allocSize;
#endif // _DEBUG

	return (void*)(pRet + CHUNK_HEAD_SIZE); //only return the data section

}

void MemoryPool::Free(void* pChunck)
{
	if (pChunck == nullptr)
		return;
	unsigned char* pRec = (unsigned char*)pChunck - CHUNK_HEAD_SIZE;
	SetNext(pRec, m_pHead);
	m_pHead = pRec;

#ifdef _DEBUG
	--m_allocSize;
#endif // _DEBUG

	pChunck = nullptr;

}


void MemoryPool::Destory()
{
	for (size_t i = 0; i < m_numBlocksInMemArray; ++i)
	{
		unsigned char* pBlock = m_ppRawMemArray[i];
		if (pBlock)
		{
			free(pBlock);
		}

#ifdef _DEBUG
		std::string logMsg = "Memory pool [ ";
		logMsg += DebugGetPoolName();
		logMsg += " ]  ";
		logMsg += "try to free ";
		logMsg += std::to_string(i + 1);
		logMsg += " th block/n";
		OutputDebugStringA(logMsg.c_str());
#endif // _DEBUG

		m_ppRawMemArray[i] = nullptr;
	}
	free(m_ppRawMemArray);
	
	Reset();

}



// inner private helper
void MemoryPool::Reset()
{
	m_ppRawMemArray = nullptr;
	m_numBlocksInMemArray = 0; 
	m_pHead = nullptr;
	m_chunkSize = 0;
	m_NumChunks = 0;
	m_Allow2GrowMemPool = true;

#ifdef _DEBUG
	m_PoolName = "No name";
	m_allocSize = 0;
	m_alloBottleneck = 0;
#endif // _DEBUG

}


bool MemoryPool::GrowMemoryPool()
{
	unsigned char** ppNewRawMem = (unsigned char**)malloc(sizeof(unsigned char*) * (m_numBlocksInMemArray + 1));
	if (ppNewRawMem == nullptr)
	{
#ifdef _DEBUG
		DebugOutPutOutOfMemoryError();
#endif // _DEBUG
		return false;
	}

	// copy old memarray to new memarray
	for (size_t i = 0; i < m_numBlocksInMemArray; i++)
	{
		ppNewRawMem[i] = m_ppRawMemArray[i];
	}

	//create new memory block to grow the pool
	unsigned char* pNewBlock = CreateNewMemoryBlock();
	if (pNewBlock == nullptr)
	{
		return false;
	}

	//link the new create block to pool
	if (m_pHead == nullptr) // this is the first created block or the pool is running out
	{
		m_pHead = pNewBlock;
	}
	else
	{
		unsigned char* pPoolCur = m_pHead;
		unsigned char* pPoolNext = GetNext(pPoolCur);
		while (pPoolNext != nullptr)
		{
			pPoolCur = pPoolNext;
			pPoolNext = GetNext(pPoolNext);
		}

		SetNext(pPoolCur, pNewBlock);
	}

	//add the new block to block array
	ppNewRawMem[m_numBlocksInMemArray] = pNewBlock;
	
	//release the memory space of old array
	for (size_t i = 0; i < m_numBlocksInMemArray; i++)
	{
		m_ppRawMemArray[i] = nullptr;
	}

	if (m_ppRawMemArray)
	{
		free(m_ppRawMemArray);
	}
	
	m_ppRawMemArray = ppNewRawMem;
	
	++m_numBlocksInMemArray;

	return true;
}



unsigned char* MemoryPool::CreateNewMemoryBlock()
{
	size_t trueChunkSize = m_chunkSize + CHUNK_HEAD_SIZE;
	size_t trueBlockSize = trueChunkSize * m_NumChunks;
	
	unsigned char* pNewBlock = (unsigned char*)malloc(trueBlockSize);

#ifdef _DEBUG
	std::string logMsg = "\n";

	logMsg += "Memory pool [ ";
	logMsg += DebugGetPoolName();
	logMsg += " ]  ";
	logMsg += "try to alloc ";
	logMsg += std::to_string(m_numBlocksInMemArray + 1);
	logMsg += " th block\n";
	OutputDebugStringA(logMsg.c_str());
#endif // _DEBUG

	if (pNewBlock == nullptr)
	{
#ifdef _DEBUG
		std::string logMsg = "Memory pool [ ";
		logMsg += DebugGetPoolName();
		logMsg += " ]  ";
		logMsg += "fail to alloc ";
		logMsg += std::to_string(m_numBlocksInMemArray + 1);
		logMsg += " th block/n";
		OutputDebugStringA(logMsg.c_str());
		DebugOutPutOutOfMemoryError();
#endif // _DEBUG
		return nullptr;
	}

	//set up the inner linker of the new block
	unsigned char* pCur = pNewBlock;
	unsigned char* pEnd = pNewBlock + trueBlockSize;
	while (pCur < pEnd)
	{
		unsigned char* pNext = pCur + trueChunkSize;
		
		if (pNext < pEnd)
		{
			SetNext(pCur, pNext);
		}
		else
		{
			SetNext(pCur, nullptr);
		}
		
		pCur += trueChunkSize;
	}

	return pNewBlock;
}



void MemoryPool::SetNext(unsigned char* pCurChunk, unsigned char* pNextChunk)
{
	unsigned char** p = (unsigned char**)pCurChunk;
	p[0] = pNextChunk;
}


unsigned char* MemoryPool::GetNext(unsigned char* pCurChunk)
{
	unsigned char** p = (unsigned char**)pCurChunk;
	return p[0];
}


void MemoryPool::DebugOutPutOutOfMemoryError()
{
	char logMsg[256];
	sprintf_s(logMsg, "fail to alloc new memory [ file: %s, line: %d ]\n", __FILE__, __LINE__);
	logMsg[255] = 0;
	OutputDebugStringA(logMsg);
}