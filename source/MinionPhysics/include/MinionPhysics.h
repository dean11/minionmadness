#ifndef MINION_PHYSICS_H
#define MINION_PHYSICS_H

//MinionPhysics is just a limited wrapper around Bullet Physics. http://www.bulletphysics.org/
#if defined MINION_PHYSICS_DLL_EXPORT
#define MINION_PHYSICS_DLL __declspec(dllexport)
#else
#define MINION_PHYSICS_DLL __declspec(dllimport)
#endif

namespace minion
{
	namespace physics
	{
		class MINION_PHYSICS_DLL MinionBody
		{

		};
		
		class MINION_PHYSICS_DLL MinionPhysics
		{
		public:
			virtual void Initiate() = 0;
		};
	}
}

#endif // !MINION_PHYSICS
