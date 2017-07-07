#include"GameInputApplication.h"
#include"Utility.h"


GameInputApplication::GameInputApplication(HINSTANCE hinstance)
:WindowBase(hinstance)
{

}

GameInputApplication::~GameInputApplication()
{

}

bool GameInputApplication::Initialize()
{
	dump_debug_msg(L"\n\nInitialize game application...\n\n");
	Input::GetSingleton();

	return true;
}


void GameInputApplication::OnExit()
{
	dump_debug_msg(L"\n\nExit game application...\n\n");
	Input::DestorySingleton();

}


void GameInputApplication::Run()
{
	if (!_initialize())
		return;

	ShowWindow(m_hMainWnd, 1);
	UpdateWindow(m_hMainWnd);

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Input::GetSingleton().Update();
			Update();
		}
	}
}


void GameInputApplication::Update()
{
	if (Input::GetSingleton().IsKeyDown(Input::eVK_LEFT))
	{
		dump_debug_msg(L"left arrow key is DOWN.\n");
	}
	if (Input::GetSingleton().IsKeyHeld(Input::eVK_RIGHT))
	{
		dump_debug_msg(L"right arrow key is HELD.\n");
	}
	if (Input::GetSingleton().IsKeyUp(Input::eVK_UP))
	{
		dump_debug_msg(L"up arrow key is UP.\n");
	}
	if (Input::GetSingleton().IsKeyDown(Input::eVK_DOWN))
	{
		dump_debug_msg(L"down arrow key is DOWN.\n");
	}


	if (Input::GetSingleton().IsKeyDown(Input::eVK_SPACE))
	{
		dump_debug_msg(L"space key is DOWN.\n");
	}


	if (Input::GetSingleton().IsKeyDown(Input::eVK_LBUTTON))
	{
		dump_debug_msg(L"left button  is DOWN,.\n");
	}
	if (Input::GetSingleton().IsKeyUp(Input::eVK_LBUTTON))
	{
		dump_debug_msg(L"left button  is UP.\n");
	}
	if (Input::GetSingleton().IsKeyHeld(Input::eVK_LBUTTON))
	{
		dump_debug_msg(L"left button  is HELD.\n");
	}

	if (Input::GetSingleton().IsMouseButtonClick(Input::eVK_LBUTTON))
	{
		dump_debug_msg(L"left button  is Click.\n");
	}

}



LRESULT	GameInputApplication::ProcessMessage(UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
		//mouse input
	case WM_LBUTTONDOWN:
	{
						   Input::GetSingleton().InjectKeyDown(Input::eVK_LBUTTON);
						   return true;
	}
		break;

	case WM_LBUTTONUP:
	{
						 Input::GetSingleton().InjectKeyUp(Input::eVK_LBUTTON);
						 return true;
	}
		break;
		//key input
	case WM_DESTROY:
	{
					   Destory();
					   return true;
	}
		break;
	case WM_KEYDOWN:
	{
					   Input::GetSingleton().InjectKeyDown(wparam);
					   return true;
	}
		break;
	case WM_KEYUP:
	{
						Input::GetSingleton().InjectKeyUp(wparam);
						return true;
	}
		break;
	case WM_SYSKEYDOWN:
	{
						 Input::GetSingleton().InjectKeyDown(wparam);
						 return true;
	}
		break;
	case WM_SYSKEYUP:
	{
						Input::GetSingleton().InjectKeyUp(wparam);
						return false;
	}
		break;
	}
	return false;
}
