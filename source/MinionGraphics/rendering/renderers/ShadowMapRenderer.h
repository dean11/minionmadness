#ifndef SHADOW_MAP_RENDERER_H
#define SHADOW_MAP_RENDERER_H

#include "../RenderTexture.h"
#include "../ShaderProgram.h"
#include "../../models/Model.h"
#include "Renderer.h"

#include <vector>

class ShadowMapRenderer		 :public Renderer
{
public:
	ShadowMapRenderer();
	virtual~ShadowMapRenderer();

	void Release() override;

	int Initialize(int width, int height);
	void QueueModel(Model* m);
	void ProcessQueuedModels();

private:
	RenderTexture renderTexture;
	ShaderProgram shaderProgram;

	std::vector<Model*> modelQueue;
	unsigned int modelQueueLenght = 0;
};


#endif // !SHADOW_MAP_RENDERER
