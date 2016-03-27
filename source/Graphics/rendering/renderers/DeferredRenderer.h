#ifndef DEFERRED_RENDERER_H
#define DEFERRED_RENDERER_H

#include "../RenderTexture.h"
#include "../ShaderProgram.h"
#include "../../models/Model.h"
#include "Renderer.h"

#include <vector>

class DeferredRenderer :public Renderer
{
public:
	DeferredRenderer();
	virtual~DeferredRenderer();

	void Release() override;
	void Clean() override;

	int Initialize(int width, int height);
	void QueueModel(Model* m);

	void ExcecuteGeometryPass();
	void ExcecuteLightPass();
	void ExcecuteFinalPass();
	
private:
	ShaderProgram shaderGeometryPass;
	ShaderProgram shaderLightPass;
	ShaderProgram shaderFinalPass;

	RenderTexture renderTexture;

	GLuint diffuseTextureID;
	GLuint positionTextureID;
	GLuint normalTextureID;
	GLuint shadowTextureID;

	std::vector<Model*> modelQueue;
	unsigned int modelQueueLenght = 0;
};


#endif // !DEFERRED_GATHER_RENDERER
