#ifndef MinionCamera_H
#define MinionCamera_H

#include "MinionPreprocess.h"
#include <memory>
#include <glm/glm.hpp>

namespace minion
{
	class MINION_GRAPHICS_API MinionCamera
	{
	public:
		static std::shared_ptr<MinionCamera> CreateCamera(float FoV, float aspect, float nearClip, float farClip, const glm::vec3& p, const glm::vec3& r);

	public:
		virtual void Update() = 0;

		virtual void RelativeRotate(float yawDelta, float pithDelta) = 0;
		virtual void RelativeMove(const glm::vec3& v) = 0;

		virtual void SetPosition(const glm::vec3& position) = 0;

		virtual glm::mat4& GetView4x4(glm::mat4&) = 0;
		virtual glm::mat4& GetProjection4x4(glm::mat4&) = 0;
		virtual glm::mat4& GetViewProjection4x4(glm::mat4&) = 0;
	};
}

#endif // !MinionCamera
