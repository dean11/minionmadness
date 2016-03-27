#include <fstream>
#include <map>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <memory>
#include <stdarg.h>

class Logger
{
public:
	enum LEVEL
	{
		LEVEL_OFF,
		LEVEL_INFO,
		LEVEL_WARNING,
		LEVEL_DEBUG,
		LEVEL_DEBUG_STDSTREAM,
	};

public:
	Logger(const char* loggerName, char* outDir);
	virtual~Logger();

	static void CreateLogger(const char* loggerName, char* outDir, bool resetLogg = true);

	static void Info(const std::string& loggerName, const char*  format, ...);
	static void Warning(const std::string& loggerName, const char*  format, ...);
	static void Debug(const std::string& loggerName, const char*  format, ...);
	static void Debug_STDStream(const std::string& loggerName, const char*  format, ...);

private:
	void write(const char*  format, va_list args);
	std::string GetTimeString();
	static Logger* SanityCheck(const std::string& loggerName, Logger::LEVEL level);

private:
	static std::map<std::string, std::shared_ptr<Logger>> loggers;

	std::string name;
	std::string outDir;
	LEVEL level;
};
