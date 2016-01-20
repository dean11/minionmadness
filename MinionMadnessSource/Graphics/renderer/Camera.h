#ifndef CAMERA_H
#define CAMERA_H

#include "../include/MinionCamera.h"

#include <glm/glm.hpp>              // GL math
#include <glm/gtx/transform.hpp>    // GL math
#include <glm/gtx/transform2.hpp>   // GL math

using glm::vec2;        // Float2
using glm::vec3;        // Float3
using glm::vec4;        // Float4
using glm::mat3;        // 4x4 matrix
using glm::mat4;        // 4x4 matrix

using glm::ivec2;		// Vector with 2 elements from GLM ( integers, used for viewport )
using glm::radians;		// For usage of radian functions
using glm::sin;			// Use sine functions
using glm::cos;			// Use cosine functions
using glm::normalize;	// Normalization
using glm::lookAt;		// LookAt function from GLM
using glm::rotate;		// Rotate function from GLM
using glm::translate;	// Translate function from GLM
using glm::perspective;	// Borrowing perspective function from GLM
using glm::inverse;     // Used when calculating normal matrix
using glm::transpose;   // Used when calculating normal matrix


class Camera : public MinionCamera
{
public:
	vec3 position;	// Position of camera
	vec3 rotation;	// Rotation/direction of camera
	vec3 up;        // Up vector of camera ( note: can be used to rotate camera by z axis, 'tilt sideways'. )

	ivec2 viewPort; // Width and height of window or viewport
	float nearClip;	// Distance of frustum beginning/ pyramid top
	float farClip;	// Distance of frostum end/ pyramid bottom
	float fovAngle;	// Slopes of frostum/ pyramid's sides

	mat4 viewMatrix;        // The cameras view matrix
	mat4 projectionMatrix;	// The cameras projection matrix
	mat3 normalMatrix;      // The cameras normal matrix

	bool freeLook;	// Determines if camera can be rotated by mouse, 'm_rotation'
	bool moveable;  // Determines if camera can be moved, 'm_position'

	float sensYaw;		// Yaw Sensitivity
	float sensPitch;	// Pitch Sensitivity

public:
	Camera();
	virtual ~Camera();

	void Update();	// calcs viewMatrix and normal matrix

	void MouseRotate(const vec2 &mouseDelta);   // Calculates and applies rotation based on mouse delta vector
	void Move(const vec3 &translation);         // Camera movement

};

#endif /* CLASSES_CAMERA_H_ */
