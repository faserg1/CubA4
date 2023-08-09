#pragma once

#include <object/IObject.hpp>
#include <model/IBlockRenderModelDefinition.hpp>
#include <physics/IBlockPhysicsDefinition.hpp>
#include <cstdint>
#include <memory>

namespace CubA4::object
{
	class IBlock :
		public virtual IObject
	{
	public:
		virtual std::shared_ptr<const CubA4::model::IBlockRenderModelDefinition> getRenderModelDefinition() const = 0;
		virtual const CubA4::physics::IBlockPhysicsDefinition &getPhysicsDefinition() const = 0;
		/// @brief Checks, if block will have multilayer logic.
		/// @details If block is multilayred, it will be in layers [1, 255] and will be placed in "heavy" part of chunk.
		/// If it's not multilayered, will be placed at layer 0 in "light" part of chunk.
		/// @return 
		virtual bool isMultilayered() const = 0;
	protected:
		explicit IBlock() = default;
		virtual ~IBlock() = default;
	};
}
