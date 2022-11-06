#pragma once

#include <object/IObject.hpp>
#include <model/IBlockRenderModelDefinition.hpp>
#include <cstdint>
#include <memory>

namespace CubA4::object
{
	class IBlock :
		public virtual IObject
	{
	public:
		virtual std::shared_ptr<const CubA4::model::IBlockRenderModelDefinition> getRenderModelDefinition() const = 0;
	protected:
		explicit IBlock() = default;
		virtual ~IBlock() = default;
	};
}
