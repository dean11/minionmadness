#ifndef TRINAGLE_H
#define TRINAGLE_H

#include "Model.h"

class Triangle :public Model
{
public:
	Triangle(const Vec3& v1, const Vec3& v2, const Vec3& v3);
	virtual~Triangle();

	void Draw() override;
	void Release() override;
	
private:
	GLuint vaoHandle;
};


#endif // !TRINAGLE
