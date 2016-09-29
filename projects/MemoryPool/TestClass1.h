#ifndef TEST_CLASS_1
#define TEST_CLASS_1

class MemoryPool;


class TestClass1
{
private:
	char data[1024];

public:

	void* operator new(size_t size);

	void operator delete(void* p);
};


#endif // !TEST_CLASS_1




