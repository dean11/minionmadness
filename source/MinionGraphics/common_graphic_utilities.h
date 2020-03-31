#ifndef COMMON_GRAPHICS_UTILITIES_H
#define COMMON_GRAPHICS_UTILITIES_H

#include "include/MinionMath.h"
#include <glm/glm.hpp>
#include <memory>

namespace minion
{
	inline void assign(const Vec2& from, glm::vec2& to)
	{
		memcpy(&to[0], &from[0], sizeof(to));
	}
	inline void assign(const glm::vec2& from, Vec2& to)
	{
		memcpy(&to[0], &from[0], sizeof(to));
	}
	inline void assign(const Vec3& from, glm::vec3& to)
	{
		memcpy(&to[0], &from[0], sizeof(to));
	}
	inline void assign(const glm::vec3& from, Vec3& to)
	{
		memcpy(&to[0], &from[0], sizeof(to));
	}
	inline void assign(const Vec4& from, glm::vec4& to)
	{
		memcpy(&to[0], &from[0], sizeof(to));
	}
	inline void assign(const glm::vec4& from, Vec4& to)
	{
		memcpy(&to[0], &from[0], sizeof(to));
	}
}

#endif // !COMMON_GRAPHICS_UTILITIES
