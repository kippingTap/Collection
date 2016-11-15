#include<iostream>
#include"ConfigurationFile.h"
using namespace std;


int main()
{
	char* pMybuffer = nullptr;
	//load config

	ConfigurationFile* pCfgManager = ConfigurationFile::GetSingelton();
	if (pCfgManager)
	{
		pCfgManager->Load("config.ini");


		pCfgManager->ChangScreenSetting(1280, 720);

		pCfgManager->Save();

	}

	ConfigurationFile::Destory();


	system("PAUSE");
	return 0;

}