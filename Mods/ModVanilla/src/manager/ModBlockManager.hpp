#pragma once

#include <manager/IModBlockManager.hpp>
#include <map>

namespace CubA4::manager
{
	class ModBlockManager : public virtual IModBlockManager
	{
	public:
		explicit ModBlockManager();
		~ModBlockManager();

		std::shared_ptr<CubA4::model::IBlockRenderModelDefinition> getBlockDefinition(const std::string &id) const override;
		void addBlockDefinition(const std::string &id, std::shared_ptr<CubA4::model::IBlockRenderModelDefinition> def);

		std::shared_ptr<CubA4::object::IBlock> getBlock(const std::string &id) const override;
		void addBlock(std::shared_ptr<CubA4::object::IBlock> block);
	private:
		std::map<std::string, std::shared_ptr<CubA4::model::IBlockRenderModelDefinition>> defs_;
		std::map<std::string, std::shared_ptr<CubA4::object::IBlock>> blocks_;
	};
}
