#include "RenderTexture.h"
#include "SaveFrameBuffer.h"

RenderTexture::RenderTexture()
{
	this->depthBufferTextureHandle = 0;
	this->depthBufferHandle = 0;
	this->fboHandle = 0;
	this->viewport[0] = 0;
	this->viewport[1] = 0;
	this->viewport[2] = 0;
	this->viewport[3] = 0;
}
RenderTexture::~RenderTexture()
{
	for each (auto var in this->renderTextures)
	{
		if (var.second.renderTargetHandle)			glDeleteRenderbuffersEXT(1, &var.second.renderTargetHandle);
		if (var.second.renderTargetTextureHandle)	glDeleteTextures(1, &var.second.renderTargetTextureHandle);
	}
	if (this->fboHandle)				glDeleteFramebuffersEXT(1, &this->fboHandle);
	if (this->depthBufferTextureHandle)	glDeleteTextures(1, &this->depthBufferTextureHandle);
	if (this->depthBufferHandle)		glDeleteRenderbuffersEXT(1, &this->depthBufferHandle);
}

void RenderTexture::BeginRenderToTextures()
{
	// Clear the render targets
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glActiveTextureARB(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
}
void RenderTexture::EndRenderToTexture()
{
	
}

void RenderTexture::Initialize(bool useDepthRT, bool useDepthTexture, int width, int height)
{
	glGenFramebuffersEXT(1, &this->fboHandle);
	this->viewport[0] = 0;
	this->viewport[1] = 0;
	this->viewport[2] = width;
	this->viewport[3] = height;

	if (useDepthRT)
	{
		//Save previous fbo
		SaveFrameBuffer s;

		// Bind the FBO so that the next operations will be bound to it
		//glBindFramebuffer(GL_FRAMEBUFFER_EXT, this->fboHandle);

		// Create and bind the depth buffer
		glGenRenderbuffers(1, &this->depthBufferHandle);
		glBindRenderbuffer(GL_RENDERBUFFER, this->depthBufferHandle);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this->depthBufferHandle);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			return;

		//if (useDepthTexture)
		//{
		//	// Generate and bind the OGL texture for the depthmap
		//	glGenTextures(1, &this->depthBufferTextureHandle);
		//	glBindTexture(GL_TEXTURE_2D, this->depthBufferTextureHandle);
		//	glTexImage2D(GL_TEXTURE_2D, 0, GL_R, width, height, 0, GL_R, GL_UNSIGNED_BYTE, NULL);
		//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		//	// Attach the texture to the FBO
		//	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, this->depthBufferTextureHandle, 0);
		//}
		//
		//glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	}
}
bool RenderTexture::AddRenderTarget(std::string renderTargetName, GLenum slot)
{
	//	if already exists, delete it and create it again
	auto res = this->renderTextures.find(renderTargetName);
	auto end = this->renderTextures.end();
	if (res != end)
	{
		return true;
	}

	SaveFrameBuffer s;
	RenderTextureItem data;

	// Bind the FBO so that the next operations will be bound to it
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, this->fboHandle);

	//Create the texture and rt
	glGenRenderbuffersEXT(1, &data.renderTargetHandle);
	glGenTextures(1, &data.renderTargetTextureHandle);

	//Bind the render target
	glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, data.renderTargetHandle);
	glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_RGBA, this->viewport[2], this->viewport[3]);
	glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, slot, GL_RENDERBUFFER_EXT, data.renderTargetHandle);

	//Bind the texture
	glBindTexture(GL_TEXTURE_2D, data.renderTargetTextureHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->viewport[2], this->viewport[3], 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	// Attach the texture to the FBO
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, slot, GL_TEXTURE_2D, data.renderTargetTextureHandle, 0);

	this->renderTextures[renderTargetName] = data;

	return true;
}
void RenderTexture::SetViewport(int viewPortX, int viewPortY, int viewPortW, int viewPortH)
{
	this->viewport[0] = viewPortX;
	this->viewport[1] = viewPortY;
	this->viewport[2] = viewPortW;
	this->viewport[3] = viewPortH;
}
GLuint RenderTexture::GetOutputTexture(std::string renderTargetName)
{
	auto res = this->renderTextures.find(renderTargetName);
	auto end = this->renderTextures.end();
	if (res == end)
		return 0;
	return this->renderTextures[renderTargetName].renderTargetTextureHandle;
}
GLuint RenderTexture::GetDepthBufferTexture() const
{
	return this->depthBufferTextureHandle;
}