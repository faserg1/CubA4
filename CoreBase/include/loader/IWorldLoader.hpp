#pragma once

namespace CubA4::world
{
	class IWorld;
}

namespace CubA4::loader
{
	class IWorldLoader
	{
	public:
		~IWorldLoader() = default;
		virtual void save(const CubA4::world::IWorld &world);
		virtual void load(CubA4::world::IWorld &world);
	protected:
		IWorldLoader() = default;
	};
}