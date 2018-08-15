#ifndef IWORLDPROVIDER_HPP
#define IWORLDPROVIDER_HPP

namespace CubA4
{
	namespace world
	{
		class IWorld;

		class IWorldProvider
		{
		public:
			virtual ~IWorldProvider() = default;

			virtual void registerWorld(IWorld *world) = 0;
			virtual void unregisterWorld(IWorld *world) = 0;
		protected:
			explicit IWorldProvider() = default;
		};
	}
}

#endif // IWORLDPROVIDER_HPP