#include "Logger.hpp"

#include <cstdarg>
#include <stdio.h>
#include <locale.h>
#include <Windows.h>

namespace Vulkwin {

	const char* Logger::levels[6] = { "/TRACE/: ", "/DEBUG/: ", "/INFO/: ", "/WARN/: ", "/ERROR/: ", "/FATAL/: " };
	const int Logger::levelColors[6] = { 
		FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
		FOREGROUND_GREEN | FOREGROUND_INTENSITY,
		FOREGROUND_BLUE | FOREGROUND_INTENSITY,
		FOREGROUND_GREEN | FOREGROUND_RED, 
		FOREGROUND_RED | FOREGROUND_INTENSITY,
		FOREGROUND_RED 
	};

	void Logger::Log(LogLevel level, const char* message, ...)
	{
		char messageBuffer[256] = { 0 };
		char argsBuffer[256] = { 0 };

		va_list args;
		va_start(args, message);
		auto argsBufferSize = vsnprintf(argsBuffer, 255, message, args);
		va_end(args);

		auto messageLength = sprintf_s(messageBuffer, 255, "%s%s\n", levels[level], argsBuffer);

		auto consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleOutputCP(1251);
		SetConsoleTextAttribute(consoleHandle, levelColors[level]);
		WriteConsoleA(consoleHandle, messageBuffer, messageLength, NULL, NULL);
		SetConsoleTextAttribute(consoleHandle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
	}
	void Logger::LogAssertion(const char* file, int line)
	{
		Logger::Log(LogLevel::Fatal, file, line);
	}
}