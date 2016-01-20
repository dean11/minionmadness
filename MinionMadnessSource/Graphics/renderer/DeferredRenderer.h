#ifndef DEFERRED_RENDERER_H
#define DEFERRED_RENDERER_H

#include <glew.h>
#include <gl/gl.h>
#include <gl/glu.h>

/**
*	A Frame Buffer Object is used by OpenGL to render into a texture. 
*	Specifically this implementation assumes that the rendered model will provide:
*	diffuse, position and normal
*/
class DeferredRenderer
{
public:
	DeferredRenderer();
	virtual~DeferredRenderer();

	/*	
	*	Creates the deffered render targets. 
	*/
	bool Create(int width, int height);

	/*
	*	Sets the viewport to use
	*/
	void SetViewport(int x, int y, int w, int h);

	/*
	*	Prepears the rendertargets for rendering
	*/
	void Begin();

	/*
	*	Unbind the rendertargets
	*/
	void End();

	GLuint	getDiffuseTexture() const { return diffuseTexture; }
	GLuint	getPositionTexture() const { return positionTexture; }
	GLuint	getNormalsTexture() const { return normalsTexture; }

private:
	GLuint	fbo; // The FBO ID
	GLuint	diffuseRT; // The diffuse render target
	GLuint	diffuseTexture; // The OpenGL texture for the diffuse render target
	GLuint	positionRT; // The position render target
	GLuint	positionTexture; // The OpenGL texture for the position render target
	GLuint	normalsRT; // The normals render target
	GLuint	normalsTexture; // The OpenGL texture for the normals render target
	GLuint	depthBuffer; // Depth buffer handle

	GLint	viewport[4];
};


#endif // !DEFERRED_RENDERER
