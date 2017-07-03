#include "stdafx.h"
#include<fstream>
#include<Windows.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>

#include "ogl_util.h"

bool ReadFile(const char* pFileName, string& outFile)
{
	ifstream f(pFileName);
	bool ret = false;
	if (f.is_open())
	{
		string line;
		while (getline(f, line))
		{

			outFile.append(line);
			outFile.append("\n");
		}
		f.close();
		ret = true;
	}
	else
	{
		OGLDEV_FILE_ERROR(pFileName);
	}

	return ret;
}

void OglError(const char* pFileName, uint line, const char* format, ...)
{
	char msg[1000];
	va_list args;
	va_start(args, format);
	VSNPRINTF(msg, sizeof(msg), format, args);
	va_end(args);

	char msg2[1000];
	_snprintf_s(msg2, sizeof(msg2), "%s:%d: %s", pFileName, line, msg);
	MessageBoxA(NULL, msg2, NULL, 0);

}

long long GetCurrentTimeMillis()
{
	//这样写就不跨平台
	return GetTickCount();

}