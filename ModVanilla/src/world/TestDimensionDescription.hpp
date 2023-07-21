#pragma once

#include <world/IDimensionDescription.hpp>
#include <world/TestWorldGenerator.hpp>

namespace CubA4::world
{
	class TestDimensionDescription :
		public virtual IDimensionDescription
	{
	public:
		TestDimensionDescription();

		std::string getId() const override;
		std::wstring getName() const override;

		std::shared_ptr<IWorldGenerator> getWorldGenerator() const override;
	private:
		std::shared_ptr<TestWorldGenerator> worldGenerator_;
	};
}