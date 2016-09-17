#ifndef BASIC_RENDERER_H
#define BASIC_RENDERER_H

#include "Renderer.h"
#include "../ShaderProgram.h"

class BasicRenderer	:public Renderer
{
public:
	BasicRenderer();
	virtual~BasicRenderer();

private:
	ShaderProgram basicShader;
};


#endif // !BASIC_RENDERER
