#include "Model.h"

#include <GID.h>

Model::Model()
{
	this->worldMatrixID = 0;
	this->rotation = glm::vec3();
	this->position = glm::vec3();
	this->textureID = 0;
	this->texture = 0;

	this->modelID = GID();
}
Model::~Model()
{

}
void Model::Render()										
{

}	
void Model::RenderShadow()									
{

}	
void Model::Animate()										
{

}	
void Model::SetPosition(float x, float y, float z)			
{

}	
void Model::SetRotation(float x, float y, float z)			
{

}	
void Model::SetScale(float x, float y, float z)				
{

}	
void Model::SetVisibleStatus(bool visible)					
{

}	
void Model::SetAnimateStatus(bool animate)					
{

}	
void Model::SetCollisionStatus(bool animate)				
{

}	
void Model::SetCastShadowStatus(bool shadow)				
{

}	
bool Model::SetDiffuseTexture(const char* filename)			
{
	return true;
}	
bool Model::SetNormalsTexture(const char* filename)			
{
	return true;
}	
bool Model::SetSpecularTexture(const char* filename)		
{
	return true;
}	
void Model::RelativePosition(float x, float y, float z)		
{

}	
void Model::RelativeRotation(float x, float y, float z)		
{

}	
void Model::RelativeScale(float x, float y, float z)		
{

}	
void Model::GetPosition(float& x, float& y, float& z) const	
{

}	
void Model::GetRotation(float& x, float& y, float& z) const	
{

}	
void Model::GetScale(float& x, float& y, float& z) const	
{

}	
bool Model::ShouldRender() const							
{
	return true;
}	
bool Model::ShouldAnimate() const							
{
	return true;
}	
bool Model::ShouldCollide() const							
{
	return true;
}	
bool Model::ShouldCastShadow() const						
{
	return true;
}	