#ifndef MinionCamera_H
#define MinionCamera_H

#include "MinionTypes.h"

namespace Minion
{
	class MinionCamera
	{
	public:
		virtual void Update() = 0;

		virtual void RelativeRotate(float yawDelta, float pithDelta) = 0;
		virtual void RelativeMove(const Vector3& delta) = 0;

		virtual Matrix4x4 GetView() = 0;
		virtual Matrix4x4 GetProjection() = 0;
		virtual Matrix4x4 GetViewProjection() = 0;
	};
}

#endif // !MinionCamera
