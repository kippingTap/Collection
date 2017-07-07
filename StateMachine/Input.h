#pragma once
#include<chrono>
#include<map>

class Input
{
public:

	enum {
		//A~Z
		eVK_A = 0x41,
		eVK_B = 0x42,
		eVK_C = 0x43,
		eVK_D = 0x44,
		eVK_E = 0x45,
		eVK_F = 0x46,
		eVK_G = 0x47,
		eVK_H = 0x48,
		eVK_I = 0x49,
		eVK_J = 0x4A,
		eVK_K = 0x4B,
		eVK_L = 0x4C,
		eVK_M = 0x4D,
		eVK_N = 0x4E,
		eVK_O = 0x4F,
		eVK_P = 0x50,
		eVK_Q = 0x51,
		eVK_R = 0x52,
		eVK_S = 0x53,
		eVK_T = 0x54,
		eVK_U = 0x55,
		eVK_V = 0x56,
		eVK_W = 0x57,
		eVK_X = 0x58,
		eVK_Y = 0x59,
		eVK_Z = 0x5A,

		//0~9
		eVK_0 = 0x30,
		eVK_1 = 0x31,
		eVK_2 = 0x32,
		eVK_3 = 0x33,
		eVK_4 = 0x34,
		eVK_5 = 0x35,
		eVK_6 = 0x36,
		eVK_7 = 0x37,
		eVK_8 = 0x38,
		eVK_9 = 0x39,


		//F1~F12
		eVK_F1 = 0x70,
		eVK_F2 = 0x71,
		eVK_F3 = 0x72,
		eVK_F4 = 0x73,
		eVK_F5 = 0x74,
		eVK_F6 = 0x75,
		eVK_F7 = 0x76,
		eVK_F8 = 0x77,
		eVK_F9 = 0x78,
		eVK_F10 = 0x79,
		eVK_F11 = 0x7A,
		eVK_F12 = 0x7B,

		//arrow key
		eVK_LEFT = 0x25,
		eVK_UP = 0x26,
		eVK_RIGHT = 0x27,
		eVK_DOWN = 0x28,


		//
		eVK_RETURN = 0x0D, //enter
		eVK_SHIFT = 0x10, //shift
		eVK_CONTROL = 0x11, //ctrl
		eVK_ESCAPE = 0x1B, //esc
		eVK_SPACE = 0x20, //space
		eVK_LSHIFT = 0xA0, //left shift
		eVK_RSHIFT = 0xA1, //right shift
		eVK_LCONTROL = 0xA2, //left ctrl
		eVK_RCONTROL = 0xA3, //right ctrl
		eVK_MENU = 0x12, //alt
		eVK_TAB = 0x09, //tab


		//moues
		eVK_LBUTTON = 0x01,
		eVK_RBUTTON = 0x02,
		eVK_MBUTTON = 0x04,
		eVK_XBUTTON1 = 0x05,
		eVK_XBUTTON2 = 0x06,

	};

	class Timer
	{
	public:
		typedef std::chrono::duration<double, std::ratio<1, 1>> seconds_t;
		Timer();
		~Timer();

		void Reset();
		seconds_t	Now_Sec();		//current time measure in sec
		seconds_t	Epoch_Sec();	//the epoch time
		seconds_t	TotalTime_Sec(); //the time elapse since the last call to reset()
	private:
		std::chrono::high_resolution_clock::time_point  m_epoch; 
	};

	class Key
	{
		friend class Input;
	private:
		enum eKeyState
		{
			eKeyState_Normal = 0,    //normal state
			eKeyState_Down,			 //key down
			eKeyState_Up,			 //key up
			eKeyState_Held,           //key held 
			eKeyState_ReadyToHeld,

			eKeyState_Click,          //for mouse
		};

		unsigned int m_code;        //virtual key code
		eKeyState	 m_state;	   //current state of the key
		Timer		 m_timer;	   //timer to update key state

		bool		 m_allowResetTimer;
		bool		 m_readyToHeld;
		bool		 m_release;		//user release the key
	public:
		Key();
		Key(unsigned int keyCode);
		~Key();

		virtual void Update();
		void		 Reset();
		virtual void InjectKeyDown();
		virtual void InjectKeyUp();
		 
	};

	class MouseKey : public Key
	{
	public:
		MouseKey();
		MouseKey(unsigned int keyCode);
		~MouseKey();

	public:
		void Update()override;


	};

public:
	typedef std::map<unsigned int, Key*> KeyboardMap;    

private:
	KeyboardMap		 m_keyboardMap;		//all keys
	double			 m_heldTreshold;	//when the time user press a key is grater then it, we think it is a vaild held event 
	double			 m_max_click_timeout;  //if the time between  mouse down and up less then, we think it is a vailed mouse click event

	void				 AddDefualtKeys();
	void				 AddMouseKey(unsigned keyCode);
	bool				 IsMousekey(unsigned int keycode);
public:
	static double	 s_defHeldThreshold;
	static double	 s_max_click_timeout;

	bool				 AddKey(unsigned int keyCode);
	bool 			 DeleteKey(unsigned int keyCode);
	bool				 HasKey(unsigned int keyCode);

	void			     InjectKeyDown(unsigned int keyCode);
	void				 InjectKeyUp(unsigned int keyCode);

	bool				 IsKeyDown(unsigned int keyCode);
	bool				 IsKeyUp(unsigned int keyCode);
	bool				 IsKeyHeld(unsigned int keyCode);

	bool				 IsMouseButtonDown(unsigned int keycode);
	bool				 IsMouseButtonHeld(unsigned int keycode);
	bool				 IsMouseButtonUp(unsigned int keycode);
	bool				 IsMouseButtonClick(unsigned int keycode);
		
	

	void				 SetKeyHeldThreshold(double threshold){ m_heldTreshold = threshold; }
	double			 GetKeyHeldThreshold(){ return m_heldTreshold; }
	void				 SetMoseClickMaxTimeout(double timeout){ m_max_click_timeout = timeout; }
	double			 GetMouseClickMaxTimeout(){ return m_max_click_timeout; }

	void				 Update();


	//singleton
private:
	static Input*	m_instance;

	Input();
	Input(const Input& other){}
	Input& operator= (const Input& other){ return *this; }

public:
	~Input();
	static Input&	GetSingleton();
	static void		DestorySingleton();
};