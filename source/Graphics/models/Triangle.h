#ifndef TRINAGLE_H
#define TRINAGLE_H

#include "Model.h"
#include "../include/MinionTypes.h"

class Triangle :public Model
{
public:
	Triangle(float height, float width);
	virtual~Triangle();

	void Draw() override;
	void Release() override;
	
private:
	GLuint vaoHandle;
};


#endif // !TRINAGLE
