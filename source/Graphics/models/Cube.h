#ifndef CUBE_H
#define CUBE_H

#include "Model.h"

class Cube :public Model
{
public:
	Cube(float width, float height, float depth);
	~Cube();

	void Draw() override;
	void Release() override;

private:
	GLuint vaoHandle;		//Mesh handle
};

#endif // !CUBE
