#ifndef MESH_LOADER_H
#define MESH_LOADER_H

#include "Mesh.h"
#include <string>

class MeshLoader
{
public:
	

public:
	static bool LoadMesh(std::string& fileName, Mesh::MinionMeshType type);

private:
	static bool LoadMinionMesh();
	static bool LoadObjMesh();
	static bool LoadFbxMesh();
};


#endif // !MESH_LOADER
