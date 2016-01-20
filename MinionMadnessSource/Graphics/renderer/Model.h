#ifndef MODELL_H
#define MODELL_H

#include "../include/MinionModel.h"
#include <glew.h>
#include <glm\glm.hpp>

class Modell	:public MinionModel
{
public:
	Modell();
	virtual~Modell();

public:
	void	Render();
	void	Animate();

	void	SetPosition(float x, float y, float z);
	void	SetRotation(float x, float y, float z);

	void	AddPosition(float x, float y, float z);
	void	AddRotation(float x, float y, float z);

	void	SetVisibleStatus(bool visible);
	void	SetAnimateStatus(bool animate);
	void	SetCollisionStatus(bool animate);

	bool	SetDiffuseTexture(const char* filename);
	bool	SetNormalsTexture(const char* filename);
	bool	SetSpecularTexture(const char* filename);

private:
	//GLSLShaderData 	m_shader; // Every model must have a shader associated (both vertex and fragment)

	GLuint			worldMatrixID; // This ID is used to pass the world matrix into the shader
	glm::vec3		rotation;	// Rotations
	glm::vec3		position;	// Positions

	GLuint			textureID;	// Texture ID used to pass the texture into the shader
	GLuint			texture;	// OpenGL texture ID
};


#endif // !MODELL
