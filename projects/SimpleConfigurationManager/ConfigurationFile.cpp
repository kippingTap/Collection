#include"ConfigurationFile.h"



//define group name and attribue name

ConfigurationFile* ConfigurationFile::m_pInstance = nullptr;

ConfigurationFile::~ConfigurationFile()
{
}

bool ConfigurationFile::Load(const std::string& configFilePath) // load cfg from the file
{
	// if call load() more than once
	_Reset();

	m_CfgfileName = configFilePath;

	m_LoadStream.open(configFilePath.c_str());
	if (m_LoadStream)
	{
		m_LoadStream.seekg(0, std::ifstream::end);
		unsigned int bufferSize = (unsigned int)m_LoadStream.tellg();
		m_LoadStream.seekg(0, std::ifstream::beg);

		char* pTempBuffer = new char[bufferSize + 1];
		if (pTempBuffer == nullptr)
		{
			if (m_LoadStream.is_open())
				m_LoadStream.close();
			m_bIsInit = false;
			return false;
		}

		m_LoadStream.read(pTempBuffer, bufferSize);
		pTempBuffer[bufferSize] = 0;

		if (!_ParseConfigFile(pTempBuffer))
		{
			m_bIsInit = false;
			if (m_LoadStream.is_open())
				m_LoadStream.close();
			if (pTempBuffer)
				delete pTempBuffer;
			return false;
		}

		m_bIsInit = true;
		delete pTempBuffer;
		if (m_LoadStream.is_open())
			m_LoadStream.close();

		return true;
	}

	if (m_LoadStream.is_open())
		m_LoadStream.close();
	m_bIsInit = false;
	return false;
}

bool ConfigurationFile::Save()  // save the cfg  change back to the file
{
	if (m_CfgfileName.empty()) // no file
		return false;
	if (m_AllConfigSetting_Vec.empty())  // no data
		return false;

	m_SaveStrem.open(m_CfgfileName.c_str(), std::ofstream::binary); //text mode to write, when it comes /n, it parse it to /r/n

	if (m_SaveStrem.is_open())
	{
		for (auto & itr_group = m_AllConfigSetting_Vec.cbegin(); itr_group != m_AllConfigSetting_Vec.cend(); ++itr_group) // each group
		{
			m_SaveStrem << '[' << itr_group->GrounpName << "]" << '\n';
			for (auto & itr_atrribute = itr_group->Attributs_Vec.cbegin(); itr_atrribute != itr_group->Attributs_Vec.cend(); ++itr_atrribute)
			{
				m_SaveStrem << itr_atrribute->Name << "=" << itr_atrribute->Value << '\n';
			}
		}

		m_bNeedSave = false;

		m_SaveStrem.close();

		return true;
	}

	return  false;
}


bool ConfigurationFile::_ParseConfigFile(const char* pCfgBuffer)
{
	if (pCfgBuffer == nullptr)
		return false;
	const char* groupBeg = pCfgBuffer;
	const char* groupEnd = nullptr;

	stAtrributeGroup tempAtrributGroup;

	while (*groupBeg != 0)
	{
		groupEnd = groupBeg + 1;
		while (*groupEnd != 0 && *groupEnd != '[')
			groupEnd++;

		if (*groupEnd == 0)
		{
			//this is the last group 

			const char* p1 = groupBeg;
			const char* p2 = p1;  // p1 and p2 point to a line beg and end
			while (*p1 != 0 && *p1 != '\n')
			{
				p2 = p1;
				while (*p2 != 0 && *p2 != '\n')
					p2++;

				if (*p1 == '[' && p2) // this is a group name line
				{
					char tempbuffer[255] = { 0 };
					unsigned int length = (p2 - 1) - (p1 + 1);
					if (length >= 255)
						length = 255 - 1;
					memcpy(tempbuffer, p1 + 1, length);
					tempAtrributGroup.GrounpName = tempbuffer;
				}
				else // this is a atrribute line
				{
					stAtrribute tempAtrribute;
					char tempBuffer[255] = { 0 };
					const char* p3 = p1;
					const char* p4 = p3;

					// name
					while (p4 && *p4 != '=')
						p4++;
					int length = p4 - p3;
					if (length >= 255)
						length = 255 - 1;
					memcpy(tempBuffer, p3, length);
					tempAtrribute.Name = tempBuffer;

					// value
					memset(tempBuffer, 0, sizeof(tempBuffer));
					length = p2 - (p4 + 1);
					if (length >= 255)
						length = 255 - 1;
					memcpy(tempBuffer, p4 + 1, length);
					tempAtrribute.Value = tempBuffer;
					tempAtrributGroup.Attributs_Vec.push_back(tempAtrribute);

				}
				p1 = *p2 == 0 ? (p2) : (p2 + 1);
			}

		}

		else if (*groupBeg == '[' && *groupEnd == '[')
		{

			//read group one by one
			const char* p1 = groupBeg;
			const char* p2 = p1;  // p1 and p2 point to a line beg and end
			while (p1 != groupEnd)
			{
				p2 = p1;
				while (*p2 != '\n')
					p2++;

				if (*p1 == '[' && p2) // this is a group name line
				{
					char tempbuffer[255] = { 0 };
					unsigned int length = (p2 - 1) - (p1 + 1);
					if (length >= 255)
						length = 255 - 1;
					memcpy(tempbuffer, p1 + 1, length);
					tempAtrributGroup.GrounpName = tempbuffer;
				}
				else // this is a atrribute line
				{
					stAtrribute tempAtrribute;
					char tempBuffer[255] = { 0 };
					const char* p3 = p1;
					const char* p4 = p3;

					// name
					while (p4 && *p4 != '=')
						p4++;
					int length = p4 - p3;
					if (length >= 255)
						length = 255 - 1;
					memcpy(tempBuffer, p3, length);
					tempAtrribute.Name = tempBuffer;

					// value
					memset(tempBuffer, 0, sizeof(tempBuffer));
					length = p2 - (p4 + 1);
					if (length >= 255)
						length = 255 - 1;
					memcpy(tempBuffer, p4 + 1, length);
					tempAtrribute.Value = tempBuffer;
					tempAtrributGroup.Attributs_Vec.push_back(tempAtrribute);

				}

				//after reading an line
				p1 = p2 + 1;    //text mode to read  when it comes  /r/n , it parse this to /n  , binary mode do nothing 
			}

		}
		m_AllConfigSetting_Vec.push_back(tempAtrributGroup);
		tempAtrributGroup.GrounpName = "";
		tempAtrributGroup.Attributs_Vec.clear();

		groupBeg = groupEnd;
	}

	return true;
}


void ConfigurationFile::Destory()
{
	if (m_pInstance != nullptr)
	{
		m_pInstance->_Reset();
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void ConfigurationFile::_Reset()
{
	m_CfgfileName = "";
	m_bIsInit = false;
	m_bNeedSave = false;
	if (m_LoadStream.is_open())
		m_LoadStream.close();
	if (m_SaveStrem.is_open())
		m_SaveStrem.close();
	if (!m_AllConfigSetting_Vec.empty())
		m_AllConfigSetting_Vec.clear();
}




bool ConfigurationFile::_GetAttribute(const std::string& grouoName, const std::string& atrributeName, unsigned int& retGropId, unsigned int& retAtrributId)const
{
	if (m_AllConfigSetting_Vec.empty())
		return false;
	for (int i = 0; i < m_AllConfigSetting_Vec.size(); ++i)
	{
		if (m_AllConfigSetting_Vec[i].GrounpName == grouoName)
		{
			for (int j = 0; j < m_AllConfigSetting_Vec[i].Attributs_Vec.size(); ++j)
			{
				if (m_AllConfigSetting_Vec[i].Attributs_Vec[j].Name == atrributeName)
				{
					retGropId = i;
					retAtrributId = j;
					return true;
				}
			}
		}
	}

	retAtrributId = -1;
	retAtrributId = -1;
	return false;
}



bool ConfigurationFile::GetScreenSetting(unsigned int& width, unsigned int& height)
{
	std::string w;
	std::string h;
	unsigned int wgroupId;
	unsigned int wAtrributeId;
	unsigned int hgroupId;
	unsigned int hAtrributeId;
	if (_GetAttribute(std::string("video"), std::string("screenwidth"), wgroupId, wAtrributeId) && _GetAttribute(std::string("video"), std::string("screeheight"), hgroupId, hAtrributeId))
	{
		w = m_AllConfigSetting_Vec[wgroupId].Attributs_Vec[wAtrributeId].Value;
		h = m_AllConfigSetting_Vec[hgroupId].Attributs_Vec[hAtrributeId].Value;
		width = atoi(w.c_str());
		height = atoi(h.c_str());
		return true;
	}
	return false;
}
bool ConfigurationFile::ChangScreenSetting(unsigned int width, unsigned int height)
{
	unsigned int wgroupId;
	unsigned int wAtrributeId;
	unsigned int hgroupId;
	unsigned int hAtrributeId;
	if (_GetAttribute(std::string("video"), std::string("screenwidth"), wgroupId, wAtrributeId) && _GetAttribute(std::string("video"), std::string("screeheight"), hgroupId, hAtrributeId))
	{
		char buffer[255] = { 0 };
		sprintf_s(buffer, "%d", width);
		m_AllConfigSetting_Vec[wgroupId].Attributs_Vec[wAtrributeId].Value = buffer;

		memset(buffer, 0, sizeof(buffer));
		sprintf_s(buffer, "%d", height);
		m_AllConfigSetting_Vec[hgroupId].Attributs_Vec[hAtrributeId].Value = buffer;
		return true;
	}
	return false;
}


ConfigurationFile* ConfigurationFile::GetSingelton()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new ConfigurationFile();
	}
	return m_pInstance;
}