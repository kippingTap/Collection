#include"TestClass1.h"
#include"MemoryPool.h"

extern MemoryPool* g_pMemoryPool;

void* TestClass1::operator new(size_t size)
{
	return g_pMemoryPool->Alloc(sizeof(TestClass1));
}

void TestClass1::operator delete(void* p)
{
	g_pMemoryPool->DeAlloc(p);
}