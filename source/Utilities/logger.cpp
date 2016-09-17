#include "logger.h"

#include <ctime>

std::map<std::string, std::shared_ptr<Logger>> Logger::loggers;

void Logger::CreateLogger(const char* loggerName, char* outDir, bool resetLogg)
{
	std::string strLoggerName = loggerName;
	auto res = loggers.find(strLoggerName);
	if (res == loggers.end())
	{
		loggers[strLoggerName];
		Logger* tmp = new Logger(loggerName, outDir);
		loggers[strLoggerName] = std::shared_ptr<Logger>(tmp);
	}
	else
	{
		loggers[strLoggerName].get()->outDir = outDir;
	}

	//Clear previous logg content
	if (resetLogg)
	{
		Logger *tmp = loggers[strLoggerName].get();
		std::string filename = tmp->outDir + tmp->name + ".logg";
	
		FILE *file = 0;
		fopen_s(&file, filename.c_str(), "w");
		if (file)	fclose(file);
	}
}

Logger::Logger(const char* loggerName, char* outDir)
{
	std::string strLoggerName = loggerName;
	auto res = loggers.find(strLoggerName);
	if (res == loggers.end())
	{
		loggers[strLoggerName] = std::shared_ptr<Logger>(new Logger(*this));
	}
	else
	{
		if (res->second.get())
			res->second.get()->outDir = outDir;
	}

	this->name = loggerName;
	this->outDir = outDir;
	this->level = LEVEL_DEBUG;
}
Logger::~Logger()
{
	
}


void Logger::Info(const std::string& loggerName, const char*  format, ...)
{
	Logger* l = Logger::SanityCheck(loggerName, Logger::LEVEL_INFO);
	if (l == nullptr)
		return;
	
	std::string s = "";
	s += "INFO";
	s += " - ";
	s += l->GetTimeString();
	s += " :: ";
	s.append(format);

	va_list args;
	va_start(args, format);
	l->write(s.c_str(), args);
	va_end(args);
}
void Logger::Warning(const std::string& loggerName, const char*  format, ...)
{
	Logger* l = Logger::SanityCheck(loggerName, Logger::LEVEL_WARNING);
	if (l == nullptr)
		return;

	std::string s = "";
	s += "WARNING";
	s += " - ";
	s += l->GetTimeString();
	s += " :: ";
	s.append(format);

	va_list args;
	va_start(args, format);
	l->write(s.c_str(), args);
	va_end(args);
}
void Logger::Debug(const std::string& loggerName, const char*  format, ...)
{
	Logger* l = Logger::SanityCheck(loggerName, Logger::LEVEL_DEBUG);
	if (l == nullptr)
		return;
	
	std::string s = "";
	s += "DEBUG";
	s += " - ";
	s += l->GetTimeString();
	s += " :: ";
	s.append(format);

	va_list args;
	va_start(args, format);
	l->write(s.c_str(), args);
	va_end(args);
}
void Logger::Debug_STDStream(const std::string& loggerName, const char*  format, ...)
{
	Logger* l = Logger::SanityCheck(loggerName, Logger::LEVEL_DEBUG_STDSTREAM);
	if (l == nullptr)
		return;

	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
}

void Logger::write(const char*  format, va_list args)
{
	std::string filename = this->outDir + this->name + ".logg";
	FILE *file = NULL;

	fopen_s(&file, filename.c_str(), "a");
	if (file)
	{
		vfprintf(file, format, args);
		
		fprintf(file, "\n");

		fclose(file);
	}
}
std::string Logger::GetTimeString()
{
	time_t t = time(0);
	const int size = 50;
	char buff[size];
	
	if (ctime_s(buff, size, &t) != 0)
		return "";

	return std::string(buff);
}
Logger* Logger::SanityCheck(const std::string& loggerName, Logger::LEVEL level)
{
	if (Logger::loggers[loggerName].get() == nullptr)
		return nullptr;

	Logger* l = Logger::loggers[loggerName].get();

	if (l->level < level)
		return nullptr;

	return l;
}

