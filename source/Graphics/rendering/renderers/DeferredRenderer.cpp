#include "DeferredRenderer.h"
#include <NoEdgeUtilities.h>
#include <iostream>

static ShaderProgram::ShaderProgramInitDesc geometryPassShaders = ShaderProgram::ShaderProgramInitDesc(SHADER_DIR"deferredGeometryPass.vs", "", "", "", SHADER_DIR"deferredGeometryPass.fs", "");
//static ShaderProgram::ShaderProgramInitDesc lightPassShaders = ShaderProgram::ShaderProgramInitDesc(SHADER_DIR"deferredGeometryPass.vs", "", "", "", SHADER_DIR"deferredGeometryPass.fs", "");
//static ShaderProgram::ShaderProgramInitDesc finalPassShaders = ShaderProgram::ShaderProgramInitDesc(SHADER_DIR"deferredGeometryPass.vs", "", "", "", SHADER_DIR"deferredGeometryPass.fs", "");


using NoEdgeUtilies::StaticArray::NumElementsOf;

DeferredRenderer::DeferredRenderer()
{
	this->modelQueueLenght = 0;
	//m_worldMatrixID = glGetUniformLocationARB(m_shader.m_programHandler, "WorldMatrix");
	//m_textureID = glGetUniformLocationARB(m_shader.m_programHandler, "tDiffuse");
}
DeferredRenderer::~DeferredRenderer()
{

}
void DeferredRenderer::Release()
{

}
void DeferredRenderer::Clean()
{
	if (!this->isClean)
	{
		std::fill(this->modelQueue.begin(), this->modelQueue.end(), nullptr);
		this->isClean = true;
		this->modelQueueLenght = 0;
	}
}
int DeferredRenderer::Initialize(int width, int height)
{
	//if (0 == this->shaderLightPass.CompileAndAttachShaderFromFile(lightPassShaders, NumElementsOf(lightPassShaders))) return 0;
	//if (0 == this->shaderGeometryPass.CompileAndAttachShaderFromFile(finalPassShaders, NumElementsOf(finalPassShaders))) return 0;


	if (0 == this->shaderGeometryPass.CreateShaderProgramFromFile(geometryPassShaders))
	{
		this->lastError = this->shaderGeometryPass.GetErrorStr();
		return 0;
	}
	

	//this->diffuseTextureID = glGetUniformLocationARB(this->shaderFinalPass, "tDiffuse");
	//this->positionTextureID = glGetUniformLocationARB(this->shaderFinalPass, "tPosition");
	//this->normalTextureID = glGetUniformLocationARB(this->shaderFinalPass, "tNormals");
	//this->shadowTextureID = glGetUniformLocationARB(this->shaderFinalPass, "tShadow");

	//this->renderTexture.Initialize(true, true, width, height);
	//if (0 == this->renderTexture.AddRenderTarget("diffuseRT", GL_COLOR_ATTACHMENT0_EXT)) return 0;
	//if (0 == this->renderTexture.AddRenderTarget("normalRT", GL_COLOR_ATTACHMENT1_EXT)) return 0;
	//if (0 == this->renderTexture.AddRenderTarget("positionRT", GL_COLOR_ATTACHMENT2_EXT)) return 0;


	return 1;
}

void DeferredRenderer::QueueModel(Model* m)
{
	if (this->modelQueueLenght < this->modelQueue.size())
	{
		this->modelQueue[modelQueueLenght] = m;
		this->modelQueueLenght ++;
	}
	else
	{
		this->modelQueue.push_back(m);
		this->modelQueueLenght++;
	}
	this->isClean = false;
}
void DeferredRenderer::ExcecuteGeometryPass()
{
	glUseProgram(this->shaderGeometryPass);
	//Set scene data :View, Projection, etc

	//Draw meshes if visible
	for (unsigned int i = 0; i < modelQueueLenght; i++)
	{
		if (this->modelQueue[i]->ShouldRender())
		{
			this->modelQueue[i]->Draw();
		}
	}

	//Reset the queuee
	Clean();
}
void DeferredRenderer::ExcecuteLightPass()
{
	this->shaderLightPass.UseShaderProgram();
}
void DeferredRenderer::ExcecuteFinalPass()
{
	this->shaderFinalPass.UseShaderProgram();
}