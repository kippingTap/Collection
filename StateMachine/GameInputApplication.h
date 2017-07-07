#pragma once
#include"WindowBase.h"
#include"Input.h"


class GameInputApplication : public WindowBase
{
public:
	GameInputApplication(HINSTANCE hinstance);
	~GameInputApplication();

	//inherit
	bool Initialize()override;
	void OnExit()override;
	void Run()override;
	LRESULT	ProcessMessage(UINT msg, WPARAM wparam, LPARAM lparam)override;

	//add
	void Update();


};