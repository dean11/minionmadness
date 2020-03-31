#include "DeferredRenderer.h"
#include <utilities.h>
#include <iostream>
#include "../../include/MinionExeptions.h"
#include "../Camera.h"

static ShaderProgram::ShaderProgramInitDesc geometryPassShaders = ShaderProgram::ShaderProgramInitDesc(SHADER_DIR("deferredGeometryPass.vs"), "", "", "", SHADER_DIR("deferredGeometryPass.fs"), "");
//static ShaderProgram::ShaderProgramInitDesc lightPassShaders = ShaderProgram::ShaderProgramInitDesc(SHADER_DIR"deferredGeometryPass.vs", "", "", "", SHADER_DIR"deferredGeometryPass.fs", "");
//static ShaderProgram::ShaderProgramInitDesc finalPassShaders = ShaderProgram::ShaderProgramInitDesc(SHADER_DIR"deferredGeometryPass.vs", "", "", "", SHADER_DIR"deferredGeometryPass.fs", "");


using utilities::StaticArray::NumElementsOf;

DeferredRenderer::DeferredRenderer()
{
	this->modelQueueLenght = 0;
	//m_worldMatrixID = glGetUniformLocationARB(m_shader.m_programHandler, "WorldMatrix");
	//m_textureID = glGetUniformLocationARB(m_shader.m_programHandler, "tDiffuse");
}
DeferredRenderer::~DeferredRenderer()
{

}


void DeferredRenderer::ProcessRenderQueue(std::shared_ptr<MinionCamera>& camera)
{
	ExcecuteGeometryPass(camera);
	ExcecuteLightPass(camera);
	ExcecuteFinalPass(camera);
}


void DeferredRenderer::Initialize(int width, int height)
{
	//if (0 == this->shaderLightPass.CompileAndAttachShaderFromFile(lightPassShaders, NumElementsOf(lightPassShaders))) return 0;
	//if (0 == this->shaderGeometryPass.CompileAndAttachShaderFromFile(finalPassShaders, NumElementsOf(finalPassShaders))) return 0;

	this->shaderGeometryPass.CreateShaderProgramFromFile(geometryPassShaders);

	this->worldViewProjectionID = 10u;

	//this->diffuseTextureID = glGetUniformLocationARB(this->shaderFinalPass, "diffuse");
	//this->positionTextureID = glGetUniformLocationARB(this->shaderFinalPass, "position");
	//this->normalTextureID = glGetUniformLocationARB(this->shaderFinalPass, "normal");
	//this->shadowTextureID = glGetUniformLocationARB(this->shaderFinalPass, "shadow");

	//this->renderTexture.Initialize(true, true, width, height);
	//if (0 == this->renderTexture.AddRenderTarget("diffuseRT", GL_COLOR_ATTACHMENT0_EXT)) return 0;
	//if (0 == this->renderTexture.AddRenderTarget("normalRT", GL_COLOR_ATTACHMENT1_EXT)) return 0;
	//if (0 == this->renderTexture.AddRenderTarget("positionRT", GL_COLOR_ATTACHMENT2_EXT)) return 0;
}


void DeferredRenderer::ExcecuteGeometryPass(std::shared_ptr<MinionCamera>& minionCamera)
{
	//Set shader
	glUseProgram(this->shaderGeometryPass);

	Camera* camera = (Camera*)minionCamera.get();
	glm::mat4x4 VP;
	camera->GetViewProjection4x4(VP);
	//memcpy(&VP[0][0], camera->GetProjection4x4(), sizeof(VP));

	//Draw meshes
	for (unsigned int i = 0; i < modelQueueLenght; i++)
	{
		//Set scene data :View, Projection, etc
		glm::mat4 MVP = VP * this->modelQueue[i]->GetMatrix();

		glUniformMatrix4fv(this->worldViewProjectionID, 1, GL_FALSE, &MVP[0][0]);

		this->modelQueue[i]->Draw();
	}

	this->modelQueueLenght = 0;
}
void DeferredRenderer::ExcecuteLightPass(std::shared_ptr<MinionCamera>& camera)
{
	this->shaderLightPass.UseShaderProgram();
}
void DeferredRenderer::ExcecuteFinalPass(std::shared_ptr<MinionCamera>& camera)
{
	this->shaderFinalPass.UseShaderProgram();
}