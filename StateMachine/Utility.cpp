#include"Utility.h"
#include<stdarg.h>
#include<Windows.h>

void dump_debug_msg(const wchar_t* ftm, ...)
{
	wchar_t msgbuffer[1024] = { 0 };
	wchar_t szbuffer[1050] = { 0 };
	
	va_list args;
	va_start(args, ftm);
	vswprintf_s(msgbuffer, ftm, args);
	swprintf_s(szbuffer, L"debug info at [file:%s, line:%d]: %ls", __FILE__, __LINE__, msgbuffer);

	OutputDebugString(msgbuffer);
}