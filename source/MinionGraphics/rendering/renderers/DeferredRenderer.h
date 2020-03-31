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

	virtual void ProcessRenderQueue(std::shared_ptr<MinionCamera>& camera) override;

	void Initialize(int width, int height);

	void ExcecuteGeometryPass(std::shared_ptr<MinionCamera>& camera);
	void ExcecuteLightPass(std::shared_ptr<MinionCamera>& camera);
	void ExcecuteFinalPass(std::shared_ptr<MinionCamera>& camera);
	
private:
	ShaderProgram shaderGeometryPass;
	ShaderProgram shaderLightPass;
	ShaderProgram shaderFinalPass;

	RenderTexture renderTexture;

	GLuint diffuseTextureID;
	GLuint positionTextureID;
	GLuint normalTextureID;
	GLuint shadowTextureID;

	GLuint worldViewProjectionID;
};


#endif // !DEFERRED_GATHER_RENDERER
