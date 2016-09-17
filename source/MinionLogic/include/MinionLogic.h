#ifndef MINION_LOGIC_H
#define MINION_LOGIC_H

#if defined MINION_LOGIC_DLL_EXPORT
#define MINION_LOGIC_DLL __declspec(dllexport)
#else
#define MINION_LOGIC_DLL __declspec(dllimport)
#endif

namespace minion
{
	namespace logic
	{
		// Basic Logic object that allows controll of a game object
		class MINION_LOGIC_DLL MinionObject
		{
			public:
			
		};
		// Player logic object allows player to control
		class MINION_LOGIC_DLL MinionPlayer :public MinionObject
		{
			public:

		};
		// An item in the world
		class MINION_LOGIC_DLL MinionItem
		{
			public:

		};
		// World logic object that controlls all logic objects added
		class MINION_LOGIC_DLL MinionWorld
		{
			public:

		};
		
		// Main class that provides methods for creating game objects
		class MinionLogic
		{
		public:
			static MinionLogic* Get();

			void Release();

			MinionObject* CreateObject();
			MinionPlayer* CreatePlayer();
			MinionWorld* CreateWorld();
			
		};

	}
}

#endif // !MINION_LOGIC
