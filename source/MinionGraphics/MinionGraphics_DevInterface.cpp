#include "MinionGraphics_DevInterface.h"

const std::string LoggDir = "./logs/";

namespace minion
{
	MinionGraphics_DevInterface::MinionGraphics_DevInterface()
	{
		//Logger::CreateLogger(LoggerName.c_str(), LoggDir.c_str());
	}
	MinionGraphics_DevInterface::~MinionGraphics_DevInterface()
	{

	}

	void MinionGraphics_DevInterface::InitializeGraphics(MinionWindow** out_window, unsigned int width, unsigned int height, const char* title)
	{
		try
		{
			Graphics_impl::InitializeGraphics(out_window, width, height, title);
		}
		catch (MinionGraphicsException& e)
		{
			
		}
		catch (ShaderProgramException& e)
		{
			//Logger l("MinionGraphics_DevInterface", "./logs/");
			//l.
		}
	}

}