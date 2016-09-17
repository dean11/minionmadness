#ifndef MESH_H
#define MESH_H

#include "Model.h"

#include <string>
#include <map>
#include <NoEdgeUtilities.h>

class Mesh :public Model
{
public:
	struct MeshData
	{
		NoEdgeUtilies::DynamicMemory::ReferenceCount counter;
		Mesh* mesh;
	};
	enum MinionMeshType
	{
		MinionMeshType_OBJ,
		MinionMeshType_FBX,
		MinionMeshType_MINION
	};

public:
	Mesh();
	~Mesh();

	int CreateMesh(const std::string& path, MinionMeshType type = MinionMeshType_OBJ);

	void Draw() override;
	void Release() override;

private:
	GLuint vaoHandle;		//Mesh handle
	GLuint worldMatrixID;	// This ID is used to pass the world matrix into the shader	

	std::string path;
	static std::map<std::string, MeshData>  meshes;
};

#endif // !MESH

