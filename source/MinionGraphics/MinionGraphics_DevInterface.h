#ifndef MINION_GRAPHICS_DEV_INTERFACE_H_H
#define MINION_GRAPHICS_DEV_INTERFACE_H_H

#include "Graphics_impl.h"


namespace minion
{
	class MinionGraphics_DevInterface :public Graphics_impl
	{
	public:
		MinionGraphics_DevInterface();
		virtual~MinionGraphics_DevInterface();


		virtual void InitializeGraphics(MinionWindow** out_window, unsigned int width, unsigned int height, const char* title) override;

	private:
	};

}

#endif // !MINION_GRAPHICS_DEV_INTERFACE_H
