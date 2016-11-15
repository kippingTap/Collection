#pragma once

#include<fstream>
#include<string>
#include<vector>


class ConfigurationFile
{

public:
	struct stAtrribute
	{
		std::string Name;
		std::string Value;
		stAtrribute() :Name(), Value() {}
	};
	struct stAtrributeGroup
	{
		std::string GrounpName;
		std::vector<stAtrribute> Attributs_Vec;
		stAtrributeGroup() :GrounpName(), Attributs_Vec() {}
		~stAtrributeGroup()
		{
			if (!Attributs_Vec.empty())
				Attributs_Vec.clear();
		}
	};

	static ConfigurationFile* GetSingelton();
	static void Destory();
private:
	static ConfigurationFile* m_pInstance;
	std::string m_CfgfileName;
	std::ifstream m_LoadStream;
	std::ofstream m_SaveStrem;
	bool m_bNeedSave;
	bool m_bIsInit;
	//container to save all the user settings
	std::vector<stAtrributeGroup> m_AllConfigSetting_Vec;

	//helper function
	bool _ParseConfigFile(const char* pCfgBuffer);
	void _Reset();
	bool _GetAttribute(const std::string& grouoName, const std::string& atrributeName, unsigned int& retGropId, unsigned int& retAtrributId)const;
public:
	bool Load(const std::string& configFilePath);
	bool Save();

	//here can add many other attribute query and set interface
	//...
	bool GetScreenSetting(unsigned int& width, unsigned int& height);
	bool ChangScreenSetting(unsigned int width, unsigned int height);

	~ConfigurationFile();
private:
	ConfigurationFile() :m_bNeedSave(false), m_bIsInit(false)
	{
	}
	ConfigurationFile(const ConfigurationFile& rhs) {}
	ConfigurationFile(ConfigurationFile&& rhs) {}
	ConfigurationFile& operator = (const ConfigurationFile& rhs) {}

};
