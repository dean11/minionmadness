#include "include/MinionGraphics.h"

#include <map>
#include <ostream>

namespace minion
{
	MinionGraphicsException::MinionGraphicsException(const char* msg, ErrorCode code)
		:std::runtime_error(msg)
	{
		this->code = code;
	}
	MinionGraphicsException::MinionGraphicsException(ErrorCode code)
		: std::runtime_error(ToText(code))
	{
		this->code = code;
	}
	MinionGraphicsException::~MinionGraphicsException()
	{
	}

	const char* MinionGraphicsException::ToText(ErrorCode code) const
	{
		static const std::map<ErrorCode, const char*> codes =
		{
			{ ErrorCode_FailedToInitializeGLFW, "FailedToInitializeGLFW" },
			{ ErrorCode_FailedToInitializeRenderWindow, "FailedToInitializeRenderWindow" },
			{ ErrorCode_FailedToInitializeGraphics, "FailedToInitializeGraphics" },
			{ ErrorCode_FailedToInitializeRenderer, "FailedToInitializeRenderer" },
			{ ErrorCode_FailedToInitializeGLEW, "FailedToInitializeGLEW" },
		};

		return codes.at(code);
	}

	std::ostream& operator<< (std::ostream& os, const MinionGraphicsException& obj)
	{
		os << "Code:> " << obj.ToText(obj.code) << "Message:> " << obj.what();
		return os;
	}
}
