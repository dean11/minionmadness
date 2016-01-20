#ifndef PLANE_H
#define PLANE_H

#include "Model.h"

class Plane :public Model
{
public:
	Plane(float xsize, float zsize, int xdivs, int zdivs, float smax = 1.0f, float tmax = 1.0f);
	virtual~Plane();

	void Render() override;
	
private:
	int faces;
};

#endif // !PLANE
