#ifndef WORLDPROVIDER_HPP
#define WORLDPROVIDER_HPP

namespace CubA4
{
	namespace world
	{
		class World;

		class WorldProvider
		{
		public:
			virtual ~WorldProvider() {}

			virtual void registerWorld(World *world) = 0;
			virtual void unregisterWorld(World *world) = 0;
		protected:
			explicit WorldProvider() {}
		};
	}
}

#endif // WORLDPROVIDER_HPP