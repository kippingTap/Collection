#pragma once


#include<Windows.h>
#include<string>



class WindowBase
{
	//c&d
public:
	WindowBase(HINSTANCE hinstance);
	virtual ~WindowBase();
protected:
	WindowBase(const WindowBase& other){}
	WindowBase& operator= (const WindowBase& other){ return *this; }


	//singleton

protected:
	static WindowBase*		s_pInstance;
public:
	static WindowBase*		GetInstance_ptr(){ return s_pInstance; }
	void					Destory();   //quit game
	//window
protected:
	HINSTANCE				m_hInstance;
	HWND					m_hMainWnd;
	
public:
	static std::wstring		m_defTitle;
	static unsigned int		m_defWidth;
	static unsigned int		m_defHeight;
	//window title
	std::wstring			m_mainWndTitle;
	const std::wstring&		GetTitle()const { return m_mainWndTitle; }
	LPCWSTR					GetTitle() { return m_mainWndTitle.c_str(); }
	void					SetTitle(const std::wstring& title); 
	void					SetTitle(LPCWSTR title);

	//window size & position
	unsigned int			m_width;
	unsigned int			m_height;
	unsigned int			GetWidth()const { return m_width; }
	unsigned int			GetHeight()const { return m_height; }
	void					SetSize(unsigned int w, unsigned int h);
	void					SetPosition(unsigned int x, unsigned int y);



	//application initialize, main loop,  exit, msg handler
public:
	virtual bool			Initialize();		
	virtual void			OnExit();				
	virtual void			Run();

	virtual	LRESULT			ProcessMessage(UINT msg, WPARAM wparam, LPARAM lparam);
	static LRESULT	CALLBACK  ProcessApplicationMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

protected:
	bool					_initialize();
	void					_onExit();
	virtual LPCWSTR			_getWindowClassName(){ return L"WindowBase"; }



};






