#ifndef MINION_PHYSICS_IMPL_H
#define MINION_PHYSICS_IMPL_H

#include "include\MinionPhysics.h"
#include "RigidBody.h"

#include <vector>
#include <bullet\btBulletCollisionCommon.h>
#include <bullet\btBulletDynamicsCommon.h>

namespace minion
{
	namespace physics
	{
		class MinionPhysics_Impl	:public MinionPhysics
		{
			public:
				MinionPhysics_Impl();
				virtual~MinionPhysics_Impl();

			public:
				void Initiate() override;

			private:
				std::vector<RigidBody*> bodys;
		};

	}
}

#endif // !MINION_PHYSICS_IMPL
