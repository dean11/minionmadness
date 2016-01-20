#ifndef MESH_H
#define MESH_H

#include "Model.h"

class Mesh :public Model
{
public:
	enum MinionMeshType
	{
		MinionMeshType_OBJ,
		MinionMeshType_FBX,
		MinionMeshType_MINION
	};

public:
	Mesh(const char* path, MinionMeshType type = MinionMeshType_OBJ);
	~Mesh();

private:

};

#endif // !MESH

