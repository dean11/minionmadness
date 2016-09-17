#ifndef RIGID_BODY_H
#define RIGID_BODY_H

#include <bullet\btBulletDynamicsCommon.h>

namespace minion
{
	namespace physics
	{
		class RigidBody
		{
		public:
			RigidBody();
			virtual~RigidBody();

		private:
			btCollisionShape* collisionShape;
		};

	}
}

#endif // !RIGID_BODY
