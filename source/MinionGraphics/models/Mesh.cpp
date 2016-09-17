#include "Mesh.h"
#include "../include/MinionGraphics.h"

std::map<std::string, Mesh::MeshData> Mesh::meshes = std::map<std::string, MeshData>();

Mesh::Mesh()
{
	
}
Mesh::~Mesh()
{

}

int Mesh::CreateMesh(const std::string& _path, MinionMeshType type)
{
	this->path = _path;

	//If the mesh is already loaded from disk to mem
	if (this->meshes.find(path) != this->meshes.end())
	{
		this->meshes[_path].counter.Incref();
	}
	else
	{
		//Load the mesh

	}

	return MinionErrorCode_SUCESS;
}
void Mesh::Draw()
{

}
void Mesh::Release()
{
	if (this->meshes[this->path].counter.Decref() == 0)
	{
		//Free resources
		delete this->meshes[this->path].mesh;

		this->meshes[this->path].mesh = 0;
		this->meshes[this->path].counter.Reset();
	}
}
