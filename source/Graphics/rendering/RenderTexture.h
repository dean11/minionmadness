#ifndef RENDER_TEXTURE_H
#define RENDER_TEXTURE_H

#include <map>
#include <string>
#include <glew.h>
#include <gl/gl.h>
#include <gl/glu.h>


class RenderTexture
{
public:
	RenderTexture();
	virtual~RenderTexture();

	void	BeginRenderToTextures();
	void	EndRenderToTexture();

	void	Initialize(bool useDepthRT, bool useDepthTexture, int width, int height);

	bool	AddRenderTarget(std::string renderTargetName, GLenum slot);
	void	SetViewport(int viewPortX, int viewPortY, int viewPortW, int viewPortH);
	GLuint	GetOutputTexture(std::string renderTargetName);
	GLuint	GetDepthBufferTexture() const;

private:
	struct RenderTextureItem
	{
		GLuint	renderTargetHandle;
		GLuint	renderTargetTextureHandle;
	};

private:
	std::map<std::string, RenderTextureItem> renderTextures;
	GLuint	fboHandle;
	GLuint	depthBufferHandle;
	GLuint	depthBufferTextureHandle;
	GLint	viewport[4];
};


#endif // !RENDER_TARGET
