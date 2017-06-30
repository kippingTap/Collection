#pragma once


template<typename T>
class SmartPointer
{

public:
	explicit SmartPointer(T* pobject);
	SmartPointer(const SmartPointer& other);
	~SmartPointer();


public:
	SmartPointer& operator = (const SmartPointer& other);
	
	T& operator * ()
	{
		return *m_pObject;
	}

	T* operator -> ()
	{
		return m_pObject;
	}

	bool Valied()
	{
		return (m_pObject != nullptr && *m_pRefCount != 0);
	}

private:
	void AddRef()
	{
		*m_pRefCount = *m_pRefCount + 1;
	}


	void DecRef()
	{ 
		*m_pRefCount = *m_pRefCount - 1;
		if (*m_pRefCount == 0)
			Release();
	}

	void Release()
	{
		delete m_pObject;
		delete m_pRefCount;
		m_pObject = nullptr;
		m_pRefCount = nullptr;
	}

private:
	T*				m_pObject;
	int*			m_pRefCount;

};




template<typename T>
SmartPointer<T>::SmartPointer(T* pobject)
{
	m_pObject = pobject;
	m_pRefCount = new int(1);
}


template<typename T>
SmartPointer<T>::SmartPointer(const SmartPointer& other)
{
	m_pObject = other.m_pObject;
	m_pRefCount = other.m_pRefCount;
	AddRef();
}


template<typename T>
SmartPointer<T>::~SmartPointer()
{
	DecRef();
}


template<typename T>
SmartPointer<T>& SmartPointer<T>::operator = (const SmartPointer& other)
{
	if (this == &other)
		return *this;

	if (m_pObject)
		DecRef();

	m_pObject = other.m_pObject;
	m_pRefCount = other.m_pRefCount;
	AddRef();
	
	return *this;
}

