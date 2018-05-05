#ifndef WORLD_MANAGER_HPP
#define WORLD_MANAGER_HPP

namespace CubA4
{
	namespace world
	{
		class WorldManager
		{
		public:
			virtual ~WorldManager() {}
		protected:
			explicit WorldManager() {}
		};
	}
}

#endif // WORLD_MANAGER_HPP