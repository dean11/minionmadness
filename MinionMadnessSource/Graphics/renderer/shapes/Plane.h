#ifndef PLANE_H
#define PLANE_H

#include "../../include/MinionModel.h"

class Plane :public MinionModel
{
public:
	void Create(float xsize, float zsize, int xdivs, int zdivs, float smax = 1.0f, float tmax = 1.0f);
	
private:
	unsigned int vaoHandle;
	int faces;
};

#endif // !PLANE
