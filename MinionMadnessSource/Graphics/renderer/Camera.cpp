#include "Camera.h"

Camera::Camera()
{
	// Set to defaults
	position  = vec3(1.0f, 2.0f, 3.0f);
	rotation  = vec3(0.0f, 0.8f, 0.0f);     // Set as target, position in world space
	up        = vec3(0.0f, 1.0f, 0.0f);

	viewPort  = ivec2(1); //used for aspect anyways, 1:1 aspect initially.
	nearClip  = 1.0f;
	farClip   = 10.0f;
	fovAngle  = 45.0f;

	viewMatrix       = mat4(1.0f);
	projectionMatrix = mat4(1.0f);
	normalMatrix     = mat3(1.0f);

	freeLook = false;
	moveable = false;

	sensYaw     = 0.4f;
	sensPitch   = 0.4f;

	// Init camera
	viewPort.x = 512;
	viewPort.y = 512;

	// View matrix
	viewMatrix = lookAt(position, rotation, up);

	// Projection matrix
	projectionMatrix = perspective(fovAngle, (float)viewPort.x / (float)viewPort.y, nearClip, farClip);

	// Calculate normal matrix
	normalMatrix = transpose(inverse( mat3(viewMatrix) )); // WRONG!


	// .fix for reposition on launch
	//position  = vec3(0.0f, 0.0f, 0.0f);
}

Camera::~Camera()
{
	// TODO Auto-generated destructor stub
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

void Camera::MouseRotate(const vec2 &mouseDelta)
{
    if (freeLook)
    {
        // Apply movement vectors to camera rotation
        rotation.x += mouseDelta.y * sensYaw;
        rotation.y += mouseDelta.x * sensPitch;

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

void Camera::Move(const vec3 &translation)
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

        if (translation.z < 0)
        {
            movement.x += (sinYRot * pitchLimit);
            movement.y += (-sinXRot);
            movement.z += (-cosYRot * pitchLimit);
        }

        if (translation.z > 0)
        {
            movement.x += (-sinYRot * pitchLimit);
            movement.y += (sinXRot);
            movement.z += (cosYRot * pitchLimit);
        }

        if (translation.x < 0)
        {
            movement.x += (-cosYRot);
            movement.z += (-sinYRot);
        }

        if (translation.x > 0)
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
