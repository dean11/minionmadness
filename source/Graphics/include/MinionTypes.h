#ifndef MINION_TYPES_H
#define MINION_TYPES_H

#include <memory>

namespace Minion
{
	struct Vector2
	{
		float x, y;
	};
	struct Vector3
	{
		float x, y, z;
	};
	struct Vector4
	{
		float x, y, z, w;

	};
	struct Color
	{
		float r, g, b, a;
	};
	struct Matrix3x3
	{
		Vector3 val[3];

		Matrix3x3(){}
		Matrix3x3(float values[3 * 3]) { memcpy(&val[0], values, sizeof(values)); }
	};
	struct Matrix4x4
	{
		Vector4 val[4];

		Matrix4x4(){}
		Matrix4x4(float values[4 * 4]) { memcpy(&val[0], values, sizeof(values)); }
	};
	struct VertexColor
	{
		Vector3 postion;
		Color color;
	};
}

#endif // !MINION_TYPES
