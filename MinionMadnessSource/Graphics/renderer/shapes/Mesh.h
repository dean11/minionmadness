#ifndef MESH_H
#define MESH_H

#include "../../include/MinionModel.h"

class Mesh :public MinionModel
{
public:
	enum MinionMeshType
	{
		MinionMeshType_OBJ,
		MinionMeshType_FBX,
		MinionMeshType_MINION
	};

public:
	Mesh();
	~Mesh();

	int Create(const char* path, MinionMeshType type = MinionMeshType_OBJ);

private:

};

#endif // !MESH

