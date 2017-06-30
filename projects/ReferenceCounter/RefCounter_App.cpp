#include<iostream>
#include<string>
#include"SmartPointer.h"
using namespace std;


class A
{
public:
	A()
	{
		cout << "Constructtion A." << endl;
	}

	~A()
	{
		cout << "Destruction A." << endl;
	}
};


class B
{
private:
	string m_msg;
public:
	B(const string& msg):m_msg(msg)
	{
		cout << "Construction B, msg: " << msg << endl;
	}
	~B()
	{
		cout << "Destruction B, msg: " << m_msg << endl;
	}

	string& GetMsg()
	{
		return m_msg;
	}

	void SetMsg(const string& msg)
	{
		m_msg = msg;
	}
};


int main()
{
	{


		SmartPointer<B> sp_b1(new B("hello world"));
		SmartPointer<B> sp_b4(new B("hello c++"));
		{
			SmartPointer<B> sp_b2(sp_b1);
			cout << "set msg form sp2: HELLO WORLD"<<endl;
			sp_b2->SetMsg("HELLO WORLD");
			

			SmartPointer<B> sp_b3 = sp_b2;
			cout << "get msg form sp3: ";
			cout << sp_b3->GetMsg() << endl;



			sp_b3 = sp_b4;
			cout << "set msg form sp3: HELLO C++" << endl;
			(*sp_b3).SetMsg("HELLO C++");
			cout << "get msg form sp4: ";
			cout << (*sp_b4).GetMsg() << endl;
		}

	}
	system("PAUSE");
	return 0;
}