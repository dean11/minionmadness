#include "MeshLoader.h"



bool MeshLoader::LoadMesh(std::string& fileName, Mesh::MinionMeshType type)
{
bool result = false;
	switch (type)
	{
		case Mesh::MinionMeshType_OBJ:
			result = MeshLoader::LoadObjMesh();
		break;

		case Mesh::MinionMeshType_FBX:
			result = MeshLoader::LoadFbxMesh();
		break;

		case Mesh::MinionMeshType_MINION:
			result = MeshLoader::LoadMinionMesh();
		break;
	}
	return true;
}

bool MeshLoader::LoadMinionMesh()
{
	return true;
}
bool MeshLoader::LoadObjMesh()
{
	return true;
}
bool MeshLoader::LoadFbxMesh()
{
	return true;
}

