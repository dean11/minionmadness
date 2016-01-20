#ifndef MODELL_H
#define MODELL_H

#include "../include/MinionModel.h"
#include <glew.h>
#include <glm\glm.hpp>
#include "bullet\btBulletCollisionCommon.h"

class Model	:public MinionModel
{
public:
	Model();
	virtual~Model();

public:
	virtual void	Render()											override;
	virtual void	RenderShadow()										override;
	virtual void	Animate()											override;
	virtual void	SetPosition(float x, float y, float z)				override;
	virtual void	SetRotation(float x, float y, float z)				override;
	virtual void	SetScale(float x, float y, float z)					override;
	virtual void	SetVisibleStatus(bool visible)						override;
	virtual void	SetAnimateStatus(bool animate)						override;
	virtual void	SetCollisionStatus(bool animate)					override;
	virtual void	SetCastShadowStatus(bool shadow)					override;
	virtual bool	SetDiffuseTexture(const char* filename)				override;
	virtual bool	SetNormalsTexture(const char* filename)				override;
	virtual bool	SetSpecularTexture(const char* filename)			override;
	virtual void	RelativePosition(float x, float y, float z)			override;
	virtual void	RelativeRotation(float x, float y, float z)			override;
	virtual void	RelativeScale(float x, float y, float z)			override;
	virtual void	GetPosition(float& x, float& y, float& z) const		override;
	virtual void	GetRotation(float& x, float& y, float& z) const		override;
	virtual void	GetScale(float& x, float& y, float& z) const		override;
	virtual bool	ShouldRender() const								override;
	virtual bool	ShouldAnimate() const								override;
	virtual bool	ShouldCollide() const								override;
	virtual bool	ShouldCastShadow() const							override;

protected:
	GLuint			vaoHandle;		//Mesh handle
	GLuint			worldMatrixID; // This ID is used to pass the world matrix into the shader

	GLuint			textureID;	// Texture ID used to pass the texture into the shader
	GLuint			texture;	// OpenGL texture ID

	glm::vec3		rotation;
	glm::vec3		position;
	glm::vec3		scale;

	bool			shouldVisible;
	bool			shouldAnimate;
	bool			shouldCollide;
	bool			shouldShadow;
	unsigned int	modelID;
};


#endif // !MODELL
