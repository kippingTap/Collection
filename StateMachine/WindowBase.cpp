#include"WindowBase.h"



std::wstring WindowBase::m_defTitle = L"Win32 Programming";
unsigned int WindowBase::m_defWidth = 800;
unsigned int WindowBase::m_defHeight = 600;
WindowBase* WindowBase::s_pInstance = nullptr;


WindowBase::WindowBase(HINSTANCE hinstance)
:m_hInstance(hinstance)
, m_hMainWnd(0)
, m_mainWndTitle(m_defTitle)
, m_width(m_defWidth)
, m_height(m_defHeight)
{
	s_pInstance = this;
}


WindowBase::~WindowBase()
{
	if (s_pInstance == this)
		s_pInstance = nullptr;
}



bool WindowBase::_initialize()
{
	//create application main window
	WNDCLASSEX wndclass			= { 0 };
	wndclass.cbSize				= sizeof(WNDCLASSEX);
	wndclass.lpszClassName		= _getWindowClassName();
	wndclass.hInstance			= m_hInstance;
	wndclass.lpfnWndProc		= ProcessApplicationMessage;
	wndclass.style				= CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;  //accetp double click, when size changed, redraw entire client area
	wndclass.hbrBackground		= (HBRUSH)COLOR_APPWORKSPACE;
	wndclass.hIcon				= LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm			= wndclass.hIcon;
	wndclass.cbWndExtra = 0;
	wndclass.cbWndExtra = 0;
	
	if (!RegisterClassEx(&wndclass))
		return false;

	m_hMainWnd = CreateWindowEx(0,
								_getWindowClassName(),
								GetTitle(),
								WS_OVERLAPPEDWINDOW,
								0,
								0,
								m_width,
								m_height,
								NULL,
								NULL,
								m_hInstance,
								NULL);

	if (!m_hMainWnd)
	{
		DWORD Error = GetLastError();
		wchar_t ErrorBuffer[1024];
		wsprintf(ErrorBuffer, L"Error creating window. Error code, decimal %d, hexadecimal %X.", Error, Error);
		MessageBox(NULL, ErrorBuffer,L"Error", MB_ICONHAND);
		return false;
	}
		

	//save current instance pointer to  the window userdata
	SetWindowLongPtr(m_hMainWnd, GWLP_USERDATA, reinterpret_cast<LONG>(this));

	//user initialize here...
	return Initialize();
}


void	WindowBase::_onExit()
{
	OnExit();
}


void WindowBase::Destory()
{
	PostQuitMessage(0);
	_onExit();
}



void WindowBase::Run()
{
	if (!_initialize())
		return;

	ShowWindow(m_hMainWnd, 1);
	UpdateWindow(m_hMainWnd);

	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

}



bool WindowBase::Initialize()
{
	// your initialize code here...

	return true;
}


void WindowBase::OnExit()
{
	//your exit code here...
}



void WindowBase::SetTitle(const std::wstring& title)
{
	m_mainWndTitle = title;
	if (m_hMainWnd)
		SetWindowText(m_hMainWnd, title.c_str());
}


void WindowBase::SetTitle(LPCWSTR title)
{
	SetTitle(std::wstring(title));
}


void WindowBase::SetSize(unsigned int w, unsigned int h)
{	
	if (w != m_width || h != m_height)
	{
		m_width = w;
		m_height = h;

		SetWindowPos(m_hMainWnd, HWND_TOPMOST, 0, 0, w, h, SWP_NOMOVE);
	}
}


void WindowBase::SetPosition(unsigned int x, unsigned int y)
{
	SetWindowPos(m_hMainWnd, HWND_TOPMOST, x, y, 0, 0, SWP_NOSIZE);
}



LRESULT	CALLBACK  WindowBase::ProcessApplicationMessage(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (s_pInstance)
	{
		if (s_pInstance->ProcessMessage(msg, wparam, lparam))
			return 0;
	}

	return DefWindowProc(hwnd, msg, wparam, lparam);
}


LRESULT	WindowBase::ProcessMessage(UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_DESTROY:
	{
					   Destory();
					   return true;
	}
		break;
	default:
		break;
	}

	return false;
}