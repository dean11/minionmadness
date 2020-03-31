#ifndef GUI_RENDERER_H
#define GUI_RENDERER_H

#include "Renderer.h"
#include "../../include/MinionCamera.h"

class GUIRenderer :public Renderer
{
public:
	GUIRenderer();
	virtual~GUIRenderer();

	virtual void ProcessRenderQueue(std::shared_ptr<MinionCamera>& camera) override;

private:

};


#endif // !GUI_RENDERER
