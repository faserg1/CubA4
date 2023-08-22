#pragma once

#include <object/IBlock.hpp>
#include <physics/DefaultBlockPhysicsDefinition.hpp>

namespace CubA4::block
{
	class TestBlock :
		public virtual CubA4::object::IBlock
	{
	public:
		explicit TestBlock(std::string id, std::shared_ptr<const CubA4::model::IBlockRenderModelDefinition> modelDef);
		~TestBlock();

		std::string getId() const override;
		std::wstring getName() const override;

		std::shared_ptr<const CubA4::model::IBlockRenderModelDefinition> getRenderModelDefinition() const override;
		const CubA4::physics::IBlockPhysicsDefinition &getPhysicsDefinition() const override;
		bool isMultilayered() const override;
	protected:
	private:
		const std::string id_;
		const std::shared_ptr<const CubA4::model::IBlockRenderModelDefinition> modelDef_;
		const CubA4::physics::DefaultBlockPhysicsDefinition blockPhysics_;
	};
}

