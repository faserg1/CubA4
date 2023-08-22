#pragma once

#include <world/IDimensionDescription.hpp>
#include <world/TestWorldGenerator.hpp>
#include <physics/DefaultPhysicsDefinition.hpp>

namespace CubA4
{
	class ICore;
}
namespace CubA4::world
{
	class TestDimensionDescription :
		public virtual IDimensionDescription
	{
	public:
		TestDimensionDescription(const CubA4::ICore &core, const manager::ModBlockManager &blockManager);

		std::string getId() const override;
		std::wstring getName() const override;

		std::shared_ptr<IWorldGenerator> getWorldGenerator() const override;
		const CubA4::physics::IWorldPhysicsDefinition &getPhysicsDefinition() const override;
	private:
		std::shared_ptr<TestWorldGenerator> worldGenerator_;
		const CubA4::physics::DefaultPhysicsDefinition physics_;
	};
}