#ifndef GUI_RENDERER_H
#define GUI_RENDERER_H

#include "Renderer.h"

class GUIRenderer :public Renderer
{
public:
	GUIRenderer();
	virtual~GUIRenderer();

	void Release() override;

private:

};


#endif // !GUI_RENDERER
