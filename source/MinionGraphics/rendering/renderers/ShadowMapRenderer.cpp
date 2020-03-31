#include "ShadowMapRenderer.h"

ShadowMapRenderer::ShadowMapRenderer()
{
	
}
ShadowMapRenderer::~ShadowMapRenderer()
{
	
}
void ShadowMapRenderer::ProcessRenderQueue(std::shared_ptr<MinionCamera>& camera)
{
	this->shaderProgram.UseShaderProgram();
	//Set scene data :View, Projection, etc

	//Draw the models
	for (unsigned int i = 0; i < modelQueueLenght; i++)
	{
		//this->modelQueue[i]->
	}
	//Reset the queuee
	std::fill(this->modelQueue.begin(), this->modelQueue.end(), nullptr);
	this->modelQueueLenght = 0;
}

int ShadowMapRenderer::Initialize(int width, int height)
{
	return 1;
}
