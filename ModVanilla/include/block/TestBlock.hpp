#pragma once

#include <object/IBlock.hpp>

namespace CubA4::block
{
	class TestBlock :
		public virtual CubA4::object::IBlock
	{
	public:
		explicit TestBlock(std::shared_ptr<const CubA4::model::IBlockRenderModelDefinition> modelDef);
		~TestBlock();

		std::string getId() const override;
		std::wstring getName() const override;

		std::shared_ptr<const CubA4::model::IBlockRenderModelDefinition> getRenderModelDefinition() const override;
	protected:
	private:
		const std::shared_ptr<const CubA4::model::IBlockRenderModelDefinition> modelDef_;
	};
}

