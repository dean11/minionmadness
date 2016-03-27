#ifndef SPHERE_H
#define SPHERE_H

#include "Model.h"

class Sphere :public Model
{
public:
	Sphere(float radius);
	virtual~Sphere();

	void Draw() override;
	void Release() override;

private:
	GLuint vaoHandle;		//Mesh handle
};

#endif // !SPHERE
