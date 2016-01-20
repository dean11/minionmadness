#ifndef SHADOW_MAP_RENDERER_H
#define SHADOW_MAP_RENDERER_H

#include <glew.h>

class ShadowMapRenderer
{
public:
	ShadowMapRenderer();
	virtual~ShadowMapRenderer();

private:
	GLuint		depthBuffer; // Depth buffer handle
};


#endif // !SHADOW_MAP_RENDERER
