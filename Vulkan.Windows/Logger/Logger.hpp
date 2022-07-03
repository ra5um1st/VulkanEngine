#pragma once

namespace Vulkwin {

#define DEBUG

#ifdef DEBUG

#define LOG_TRACE(message, ...) Logger::Log(LogLevel::Trace, message, ##__VA_ARGS__)
#define LOG_DEBUG(message, ...) Logger::Log(LogLevel::Debug, message, ##__VA_ARGS__)
#define LOG_INFO(message, ...) Logger::Log(LogLevel::Info, message, ##__VA_ARGS__)
#define LOG_WARN(message, ...) Logger::Log(LogLevel::Warn, message, ##__VA_ARGS__)
#define LOG_ERROR(message, ...) Logger::Log(LogLevel::Error, message, ##__VA_ARGS__)
#define LOG_FATAL(message, ...) Logger::Log(LogLevel::Fatal, message, ##__VA_ARGS__)

#define	LOG_ASSERT(value)								\
	if (value) {}										\
	else												\
	{													\
		Logger::LogAssertion(__FILE__, __LINE__);		\
	}													\
}

#endif // _DEBUG_

	enum LogLevel {
		Trace,
		Debug,
		Info,
		Warn,
		Error,
		Fatal
	};

	class Logger
	{
	public:

		//TODO: separate console and file logging
		static void Log(LogLevel level, const char* message, ...);
		static void LogAssertion(const char* file, int line);

	private:
		static const char* levels[];
		static const int levelColors[];
	};
}