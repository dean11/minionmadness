#ifndef CAMERA_H
#define CAMERA_H

#include "../include/MinionCamera.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> 
#include <glm/gtx/transform2.hpp>

using namespace glm;
using namespace minion;

namespace minion
{
	class Camera : public MinionCamera
	{
	public:
		Camera(float FoV, float aspect, float nearClip, float farClip, const glm::vec3& p, const glm::vec3& r);
		virtual ~Camera();

		void Update() override;
		void RelativeRotate(float yawDelta, float pithDelta) override;
		void RelativeMove(const glm::vec3& translationVec) override;

		void SetPosition(const glm::vec3& position) override;

		glm::mat4& GetView4x4(glm::mat4&) override;
		glm::mat4& GetProjection4x4(glm::mat4&) override;
		glm::mat4& GetViewProjection4x4(glm::mat4&) override;
	
	private:
		vec3 position;	
		vec3 rotation;	
		vec3 up;        

		float aspect;	
		float nearClip;	
		float farClip;	
		float fovAngle;	

		mat4 viewMatrix;        
		mat4 projectionMatrix;	
		mat3 normalMatrix;      

		bool freeLook;	
		bool moveable;  

		float sensYaw;		
		float sensPitch;	
	};
}
#endif /* CLASSES_CAMERA_H_ */
