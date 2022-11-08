#pragma once

#include <world/IWorldDefinition.hpp>

namespace CubA4::world
{
	class TestWorldDefinition :
		public virtual CubA4::world::IWorldDefinition
	{
	public:
		explicit TestWorldDefinition();
		~TestWorldDefinition();

		std::string getId() const override;
		std::wstring getName() const override;
	protected:
	private:
	};
}
