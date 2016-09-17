#ifndef CAMERA_H
#define CAMERA_H

#include "../include/MinionCamera.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> 
#include <glm/gtx/transform2.hpp>

using namespace glm;
using namespace Minion;

namespace Minion
{
	class Camera : public MinionCamera
	{
	public:
		Camera();
		virtual ~Camera();

		void Update() override;
		void RelativeRotate(float yawDelta, float pithDelta) override;
		void RelativeMove(float delta[4]) override;
		float* GetView4x4() override;
		float* GetProjection4x4() override;
		float* GetViewProjection4x4() override;
	
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
