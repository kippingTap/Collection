#include"Input.h"


//timer
Input::Timer::Timer()
{
	Reset();
}

Input::Timer::~Timer()
{

}

Input::Timer::seconds_t Input::Timer::Now_Sec()
{
	auto now = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<seconds_t>(now.time_since_epoch());
}

Input::Timer::seconds_t Input::Timer::Epoch_Sec()
{
	return std::chrono::duration_cast<seconds_t>(m_epoch.time_since_epoch());
}

Input::Timer::seconds_t Input::Timer::TotalTime_Sec()
{
	auto now = std::chrono::high_resolution_clock::now();
	return std::chrono::duration_cast<seconds_t>(now-m_epoch);
}

void Input::Timer::Reset()
{
	m_epoch = std::chrono::high_resolution_clock::now();
}




//key

Input::Key::Key()
{
	m_code = -1;
	Reset();
}

Input::Key::Key(unsigned int keyCode)
{
	m_code = keyCode;
	Reset();
}

Input::Key::~Key()
{

}


void Input::Key::Update()
{
	if (m_state == eKeyState_Normal)
		return;

	if (m_release)
	{
		m_state = eKeyState_Normal;
		m_release = false;
	}

	if (m_readyToHeld)
	{
		m_state = eKeyState_ReadyToHeld;
		m_readyToHeld = false;
	}

	if ( m_state == eKeyState_Down)
	{
		m_readyToHeld = true;
	}

	if (m_state == eKeyState_ReadyToHeld)
	{
		Timer::seconds_t now = m_timer.Now_Sec();
		double detal = now.count() - m_timer.Epoch_Sec().count();
		if (detal >= Input::GetSingleton().GetKeyHeldThreshold())
		{
			m_state = eKeyState_Held;
		}
	}

	if (m_state == eKeyState_Up)
	{
		m_release = true;
	}

}

void Input::Key::Reset()
{
	m_state = eKeyState_Normal;
	m_timer.Reset();
	m_allowResetTimer = true;
	m_release = false;
	m_readyToHeld = false;
}

void Input::Key::InjectKeyDown()
{
	if (m_allowResetTimer)
	{
		m_timer.Reset();
		m_state = eKeyState_Down;
		
		m_allowResetTimer = false;
	}
}

void Input::Key::InjectKeyUp()
{
	m_state = eKeyState_Up;
	m_allowResetTimer = true;
}


//mouse button


 Input::MouseKey::MouseKey()
{

}

Input::MouseKey::MouseKey(unsigned int keyCode)
:Input::Key(keyCode)
{

}

Input::MouseKey::~MouseKey()
{

}

void Input::MouseKey::Update()
{
	if (m_state == eKeyState_Normal)
		return;

	if (m_release)
	{
		
		double detal = m_timer.Now_Sec().count() - m_timer.Epoch_Sec().count();
		if (detal <= Input::GetSingleton().GetMouseClickMaxTimeout() && m_state != eKeyState_Click)
		{
			m_state = eKeyState_Click;
		}
		else
		{
			m_state = eKeyState_Normal;
			m_release = false;
		}

	}

	if (m_readyToHeld)
	{
		m_state = eKeyState_ReadyToHeld;
		m_readyToHeld = false;
	}

	if (m_state == eKeyState_Down)
	{
		m_readyToHeld = true;
	}

	if (m_state == eKeyState_ReadyToHeld)
	{
		Timer::seconds_t now = m_timer.Now_Sec();
		double detal = now.count() - m_timer.Epoch_Sec().count();
		if (detal >= Input::GetSingleton().GetKeyHeldThreshold())
		{
			m_state = eKeyState_Held;
		}
	}

	if (m_state == eKeyState_Up)
	{
		m_release = true;
	}
}




//input 

Input* Input::m_instance = nullptr;
double Input::s_defHeldThreshold = 0.8;
double Input::s_max_click_timeout = 0.4;


Input::Input()
{

}

Input::~Input()
{
	for (auto& key : m_keyboardMap)
	{
		delete key.second;
	}
	m_keyboardMap.clear();
}

Input&	Input::GetSingleton()
{
	if (!m_instance)
	{
		m_instance = new Input();
		m_instance->AddDefualtKeys();
		m_instance->SetKeyHeldThreshold(Input::s_defHeldThreshold);
		m_instance->SetMoseClickMaxTimeout(Input::s_max_click_timeout);
	}

	return *m_instance;
}

void Input::DestorySingleton()
{
	if (m_instance)
		delete m_instance;
	m_instance = nullptr;
}


bool Input::AddKey(unsigned int keyCode)
{
	if (HasKey(keyCode))
		return false;

	Key* pKey = new Key(keyCode);
	m_keyboardMap[keyCode] = pKey;
	return true;
}

void	 Input::AddMouseKey(unsigned keyCode)
{
	if (HasKey(keyCode))
		return;
	MouseKey* pKey = new MouseKey(keyCode);
	m_keyboardMap[keyCode] = pKey;

}


void Input::AddDefualtKeys()
{
	// A~Z
	for (unsigned int code = eVK_A; code <= eVK_Z; ++code)
	{
		AddKey(code);
	}

	//0~9
	for (unsigned int code = eVK_0; code <= eVK_9; ++code)
	{
		AddKey(code);
	}

	//F1~FF12
	for (unsigned int code = eVK_F1; code <= eVK_F12; ++code)
	{
		AddKey(code);
	}

	//arrow keys
	for (unsigned int code = eVK_LEFT; code <= eVK_DOWN; ++code)
	{
		AddKey(code);
	}

	AddKey(eVK_RETURN);
	AddKey(eVK_SHIFT);
	AddKey(eVK_CONTROL);
	AddKey(eVK_ESCAPE);
	AddKey(eVK_SPACE);
	AddKey(eVK_LSHIFT);
	AddKey(eVK_RSHIFT);
	AddKey(eVK_LCONTROL);
	AddKey(eVK_RCONTROL);
	AddKey(eVK_MENU);
	AddKey(eVK_TAB);

	//mouse 
	AddMouseKey(eVK_LBUTTON);
	AddMouseKey(eVK_RBUTTON);
	AddMouseKey(eVK_MBUTTON);
	AddMouseKey(eVK_XBUTTON1);
	AddMouseKey(eVK_XBUTTON2);
}


bool Input::DeleteKey(unsigned int keyCode)
{
	KeyboardMap::iterator pos = m_keyboardMap.find(keyCode);
	if (pos == m_keyboardMap.end())
		return false;

	delete pos->second;
	m_keyboardMap.erase(pos);
	return true;
}


bool Input::HasKey(unsigned int keyCode)
{
	return m_keyboardMap.find(keyCode) != m_keyboardMap.end();
}


bool	 Input::IsMousekey(unsigned int keycode)
{
	return keycode == eVK_LBUTTON || keycode == eVK_RBUTTON || keycode == eVK_MBUTTON || keycode == eVK_XBUTTON1 || keycode == eVK_XBUTTON2;
}




void Input::InjectKeyDown(unsigned int keyCode)
{
	if (HasKey(keyCode))
	{
		Key* pkey = m_keyboardMap[keyCode];
		if (pkey)
			pkey->InjectKeyDown();
	}
}





void Input::InjectKeyUp(unsigned int keyCode)
{
	if (HasKey(keyCode))
	{
		Key* pkey = m_keyboardMap[keyCode];
		if (pkey)
			pkey->InjectKeyUp();
	}
}


bool Input::IsKeyDown(unsigned int keyCode)
{
	if (HasKey(keyCode))
	{
		Key* pkey = m_keyboardMap[keyCode];
		if (pkey)
			return pkey->m_state == Key::eKeyState_Down;
	}
	return false;
}


bool Input::IsKeyUp(unsigned int keyCode)
{
	if (HasKey(keyCode))
	{
		Key* pkey = m_keyboardMap[keyCode];
		if (pkey)
			return pkey->m_state == Key::eKeyState_Up;
	}
	return false;
}


bool Input::IsKeyHeld(unsigned int keyCode)
{
	if (HasKey(keyCode))
	{
		Key* pkey = m_keyboardMap[keyCode];
		if (pkey)
			return pkey->m_state == Key::eKeyState_Held;
	}
	return false;
}



bool	 Input::IsMouseButtonDown(unsigned int keycode)
{
	if (!IsMousekey(keycode))
		return false;

	return IsKeyDown(keycode);
}


bool	 Input::IsMouseButtonHeld(unsigned int keycode)
{
	if (!IsMousekey(keycode))
		return false;

	return IsKeyHeld(keycode);

}


bool	 Input::IsMouseButtonUp(unsigned int keycode)
{
	if (!IsMousekey(keycode))
		return false;

	return IsKeyUp(keycode);
}


bool	 Input::IsMouseButtonClick(unsigned int keycode)
{
	if (!IsMousekey(keycode))
		return false;

	Key* pkey = m_keyboardMap[keycode];
	if (pkey)
		return pkey->m_state == Key::eKeyState_Click;

	return false;
}


void Input::Update()
{
	for (auto& key : m_keyboardMap)
	{
		key.second->Update();
	}
}