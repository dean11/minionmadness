#ifndef SHADOW_MAP_RENDERER_H
#define SHADOW_MAP_RENDERER_H

#include "../RenderTexture.h"
#include "../ShaderProgram.h"
#include "../../models/Model.h"
#include "../../include/MinionCamera.h"
#include "Renderer.h"

#include <vector>

class ShadowMapRenderer		 :public Renderer
{
public:
	ShadowMapRenderer();
	virtual~ShadowMapRenderer();

	virtual void ProcessRenderQueue(std::shared_ptr<MinionCamera>& camera) override;

	int Initialize(int width, int height);

private:
	RenderTexture renderTexture;
	ShaderProgram shaderProgram;
};


#endif // !SHADOW_MAP_RENDERER
