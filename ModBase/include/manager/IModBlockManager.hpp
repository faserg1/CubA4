#pragma once

#include <model/IBlockRenderModelDefinition.hpp>
#include <object/IBlock.hpp>
#include <memory>
#include <string>

namespace CubA4::manager
{
	class IModBlockManager
	{
	public:
		virtual ~IModBlockManager() = default;

		virtual std::shared_ptr<CubA4::model::IBlockRenderModelDefinition> getBlockDefinition(const std::string &id) const = 0;
		virtual std::shared_ptr<CubA4::object::IBlock> getBlock(const std::string &id) const = 0;
	protected:
		explicit IModBlockManager() = default;
	private:
	};
}
