#ifndef MINION_EXEPTIONS_H
#define MINION_EXEPTIONS_H

#include "MinionPreprocess.h"

namespace minion
{
	namespace Exceptions
	{
		class MINION_GRAPHICS_API ShaderException :public std::runtime_error
		{
		public:
			ShaderException(const char* msg)
				:std::runtime_error(msg) {}
		};
	}
}

#endif // !MINION_EXEPTIONS
