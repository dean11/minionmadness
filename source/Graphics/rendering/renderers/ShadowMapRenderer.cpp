#include "ShadowMapRenderer.h"

ShadowMapRenderer::ShadowMapRenderer()
{
	
}
ShadowMapRenderer::~ShadowMapRenderer()
{
	
}	
void ShadowMapRenderer::Release()
{

}
int ShadowMapRenderer::Initialize(int width, int height)
{
	return 1;
}
void ShadowMapRenderer::QueueModel(Model* m)
{
	if (this->modelQueueLenght < this->modelQueue.size())
	{
		this->modelQueue[modelQueueLenght] = m;
		this->modelQueueLenght++;
	}
	else
	{
		this->modelQueue.push_back(m);
		this->modelQueueLenght++;
	}
}

void ShadowMapRenderer::ProcessQueuedModels()
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