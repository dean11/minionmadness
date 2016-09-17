#include "Camera.h"

namespace Minion
{
	Camera::Camera()
	{
		// Set to defaults
		this->position			= vec3(0.0f, 0.0f, 0.0f);
		this->rotation			= vec3(0.0f, 0.0f, 0.0f);
		this->up				= vec3(0.0f, 1.0f, 0.0f);
		this->aspect			= 0.0f;
		this->nearClip			= 1.0f;
		this->farClip			= 10.0f;
		this->fovAngle			= 45.0f;
		this->viewMatrix		= mat4(1.0f);
		this->projectionMatrix	= mat4(1.0f);
		this->normalMatrix		= mat3(1.0f);
		this->freeLook			= false;
		this->moveable			= false;
		this->sensYaw			= 0.4f;
		this->sensPitch			= 0.4f;

		// View matrix
		this->viewMatrix = lookAt(position, rotation, up);

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

	void Camera::RelativeMove(float translation[3])
	{
		if (moveable)
		{
			vec3 movement;

			// Get Sine and Cosine of x and y
			float sinXRot = sin(radians(rotation.x));
			float cosXRot = cos(radians(rotation.x));

			float sinYRot = sin(radians(rotation.y));
			float cosYRot = cos(radians(rotation.y));

			// '''Set y rotation limit. 'Cannot bend more than 90 degrees up and back
			// (This cancels out moving on the Z axis when we're looking up or down)
			float pitchLimit = cosXRot;

			if (translation[2] < 0)
			{
				movement.x += (sinYRot * pitchLimit);
				movement.y += (-sinXRot);
				movement.z += (-cosYRot * pitchLimit);
			}

			if (translation[2] > 0)
			{
				movement.x += (-sinYRot * pitchLimit);
				movement.y += (sinXRot);
				movement.z += (cosYRot * pitchLimit);
			}

			if (translation[0] < 0)
			{
				movement.x += (-cosYRot);
				movement.z += (-sinYRot);
			}

			if (translation[0] > 0)
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

	float* Camera::GetView4x4()
	{
		return &this->viewMatrix[0].x;
	}
	float* Camera::GetProjection4x4()
	{
		return &this->projectionMatrix[0].x;
	}
	float* Camera::GetViewProjection4x4()
	{
		mat4 vp = this->viewMatrix * this->projectionMatrix;

		return &vp[0].x;
	}
}