#include<Windows.h>
#include"GameInputApplication.h"

INT WINAPI	WinMain(HINSTANCE hinstance, HINSTANCE, LPSTR cmdLine, int cmdShow)
{

	GameInputApplication gameApp(hinstance);
	gameApp.SetTitle(L"Game Input Demo");
	gameApp.Run();

	return 0;
}