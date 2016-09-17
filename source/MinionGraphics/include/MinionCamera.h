#ifndef MinionCamera_H
#define MinionCamera_H

namespace Minion
{
	class MinionCamera
	{
	public:
		virtual void Update() = 0;

		virtual void RelativeRotate(float yawDelta, float pithDelta) = 0;
		virtual void RelativeMove(float delta[3]) = 0;

		virtual float* GetView4x4() = 0;
		virtual float* GetProjection4x4() = 0;
		virtual float* GetViewProjection4x4() = 0;
	};
}

#endif // !MinionCamera
