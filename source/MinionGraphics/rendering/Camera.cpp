#include "Camera.h"
#include "../common_graphic_utilities.h"

namespace minion
{
	std::shared_ptr<MinionCamera> MinionCamera::CreateCamera(float FoV, float aspect, float nearClip, float farClip, const glm::vec3& p, const glm::vec3& r)
	{
		return std::shared_ptr<MinionCamera>(new Camera(FoV, aspect, nearClip, farClip, p, r));
	}


	Camera::Camera(float FoV, float aspect, float nearClip, float farClip, const glm::vec3& p, const glm::vec3& r)
	{
		// Set to defaults
		this->position			= p;
		this->rotation			= r;
		this->up				= vec3(0.0f, 1.0f, 0.0f);
		this->aspect			= aspect;
		this->nearClip			= nearClip;
		this->farClip			= farClip;
		this->fovAngle			= FoV;
		this->viewMatrix		= mat4(1.0f);
		this->projectionMatrix	= mat4(1.0f);
		this->normalMatrix		= mat3(1.0f);
		this->freeLook			= false;
		this->moveable			= false;
		this->sensYaw			= 0.4f;
		this->sensPitch			= 0.4f;

		// View matrix
		this->viewMatrix = lookAt(this->position, this->rotation, up);

		// Projection matrix
		this->projectionMatrix = perspective(this->fovAngle, this->aspect, this->nearClip, this->farClip);

		// Calculate normal matrix
		normalMatrix = transpose(inverse( mat3(viewMatrix) )); // WRONG!
	}

	Camera::~Camera()
	{
	}

	void Camera::Update()
	{
		// As identity
		if (freeLook || moveable)
		{
			viewMatrix = mat4(1.0f);
		}

		// Rotate
		if (freeLook)
		{
			viewMatrix *= rotate(rotation.x, vec3(1.0f, 0.0f, 0.0f));    // cam x-axis (vertical)
			viewMatrix *= rotate(rotation.y, vec3(0.0f, 1.0f, 0.0f));    // cam y-axis (horizontal)
			viewMatrix *= translate(position);
		}

		// Translate
		if (moveable)
		{
			viewMatrix *= translate(position);
		}

		// Calculate normal matrix
		if (freeLook || moveable)
		{
			normalMatrix = transpose(inverse( mat3(viewMatrix) ));
		}
	}

	void Camera::RelativeRotate(float yawDelta, float pithDelta)
	{
		if (freeLook)
		{
			// Apply movement vectors to camera rotation
			rotation.x += yawDelta * sensYaw;
			rotation.y += pithDelta * sensPitch;

			// Limit looking up (Dont break the cameraman's neck)
			if (rotation.x < -90.0f)
			{
				rotation.x = -90.0f;
			}

			// Limit looking down (Cannot see through cameraman's tummy)
			if (rotation.x > 90.0f)
			{
				rotation.x = 90.0f;
			}

			// Limit Y rotation angles to range of 0-360
			if (rotation.y < 0.0f)
			{
				rotation.y += 360.0f;
			}
			if (rotation.y > 360.0f)
			{
				rotation.y -= 360.0f;
			}
		}
	}
	void Camera::RelativeMove(const glm::vec3& v)
	{
		if (moveable)
		{
			vec3 movement;

			// Get Sine and Cosine of x and y
			float sinXRot = sin(radians(this->rotation.x));
			float cosXRot = cos(radians(this->rotation.x));

			float sinYRot = sin(radians(this->rotation.y));
			float cosYRot = cos(radians(this->rotation.y));

			// '''Set y rotation limit. 'Cannot bend more than 90 degrees up and back
			// (This cancels out moving on the Z axis when we're looking up or down)
			float pitchLimit = cosXRot;

			if (v.z < 0)
			{
				movement.x += (sinYRot * pitchLimit);
				movement.y += (-sinXRot);
				movement.z += (-cosYRot * pitchLimit);
			}

			if (v.z > 0)
			{
				movement.x += (-sinYRot * pitchLimit);
				movement.y += (sinXRot);
				movement.z += (cosYRot * pitchLimit);
			}

			if (v.x < 0)
			{
				movement.x += (-cosYRot);
				movement.z += (-sinYRot);
			}

			if (v.x > 0)
			{
				movement.x += (cosYRot);
				movement.z += (sinYRot);
			}

			// Normalize movement vector
			normalize(movement);

			// Change position of cam
			position += movement;
		}
	}

	void Camera::SetPosition(const glm::vec3& position)
	{
		this->position = position;
	}

	glm::mat4& Camera::GetView4x4(glm::mat4& m)
	{
		return (m = this->viewMatrix);
	}
	glm::mat4& Camera::GetProjection4x4(glm::mat4& m)
	{
		return (m = this->projectionMatrix);
	}
	glm::mat4& Camera::GetViewProjection4x4(glm::mat4& m)
	{
		return (m = this->viewMatrix * this->projectionMatrix);
	}
}