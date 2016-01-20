#include <fstream>
#include <map>

class Logger
{
	public:
		enum LEVEL
		{
			LEVEL_OFF,
			LEVEL_INFO,
			LEVEL_WARNING,
			LEVEL_DEBUG,
		};
		static std::map<const char*, Logger*> loggers;
		const char* path = "";
		LEVEL level = LEVEL_DEBUG;

		static Logger* CreateLogger(const char* clazz, const char* file)
		{
			auto res = loggers.find(clazz);
			if (res != loggers.end())
			{
				loggers[clazz] = new Logger(file);
			}

			return loggers[clazz];
		}

		Logger(const char*  path)
		{
			this->path = path;
		}
		void write(const char*  line)
		{
			const char* dir = Path.GetDirectoryName(path);
			if (!Directory.Exists(dir))
			{
				DirectoryInfo inf = Directory.CreateDirectory(dir);
			}
			if (!File.Exists(this.path))
			{
				try
				{
					File.Create(this.path).Close();
				}
				catch (Exception)
				{
				}
			}

			using (StreamWriter file = new StreamWriter(this.path, true))
			{
				file.WriteLine(line);
			};
		}

		void info(const char*  text)
		{
			if (level < LEVEL_INFO)
			{
				return;
			}
			std::string s = "";
			s += "INFO";
			s += " - ";
			s += DateTime.Now.ToLongTimeString();
			s += " :: ";
			s += text;

			this->write(s);
		}
		void warning(const char*  text)
		{
			if (level < LEVEL_WARNING)
			{
				return;
			}
			std::string s = "";
			s += "WARNING";
			s += " - ";
			s += DateTime.Now.ToLongTimeString();
			s += " :: ";
			s += text;

			this->write(s);
		}
		void debug(const char*  text)
		{
			if (level < LEVEL_DEBUG)
			{
				return;
			}
			String s = "";
			s += "DEBUG";
			s += " - ";
			s += DateTime.Now.ToLongTimeString();
			s += " :: ";
			s += text;

			this->write(s);
		}
};
