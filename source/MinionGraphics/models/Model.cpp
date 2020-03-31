#include "Model.h"

#include <GID.h>

Model::Model()
{
	this->rotation = glm::vec3();
	this->position = glm::vec3();

	this->modelID = utilities::GID();
}
Model::~Model()
{
	
}

//######################################################################

void Model::SetPosition(float x, float y, float z)			
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
}	
void Model::SetRotation(float x, float y, float z)			
{
	this->rotation.x = x;
	this->rotation.y = y;
	this->rotation.z = z;
}	
void Model::SetScale(float x, float y, float z)				
{
	this->scale.x = x;
	this->scale.y = y;
	this->scale.z = z;
}	
void Model::SetVisibleStatus(bool visible)					
{
	this->shouldRender = visible;
}	
void Model::SetAnimateStatus(bool animate)					
{
	this->shouldAnimate = animate;
}	
void Model::SetCollisionStatus(bool collide)				
{
	this->shouldCollide = collide;
}	
void Model::SetCastShadowStatus(bool shadow)				
{
	this->shouldShadow = shadow;
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
void Model::RelativeMovement(float x, float y, float z)		
{

}	
void Model::RelativeRotation(float x, float y, float z)		
{

}	
void Model::RelativeScaling(float x, float y, float z)		
{
	
}	
void Model::GetPosition(float& x, float& y, float& z) const	
{
	x = this->position.x;
	y = this->position.y;
	z = this->position.z;
}	
void Model::GetRotation(float& x, float& y, float& z) const	
{
	x = this->rotation.x;
	y = this->rotation.y;
	z = this->rotation.z;
}	
void Model::GetScale(float& x, float& y, float& z) const	
{
	x = this->scale.x;
	y = this->scale.y;
	z = this->scale.z;
}	
bool Model::ShouldRender() const							
{
	return this->shouldRender;
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

glm::mat4 Model::GetMatrix() const
{
	glm::mat4 mat;
	mat[0];
	mat[1];
	mat[2] = glm::vec4(this->position, 0.0);
	mat[3];
	return mat;
}