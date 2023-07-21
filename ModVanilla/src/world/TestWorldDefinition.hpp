#pragma once

#include <world/IWorldDefinition.hpp>
#include <world/TestDimensionDescription.hpp>

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

		const DimensionDescriptionCollection &getDimensionDescriptions() const override;
	protected:
	private:
		DimensionDescriptionCollection descriptions_;
		std::unique_ptr<TestDimensionDescription> testDimensionDescription_;
	};
}
