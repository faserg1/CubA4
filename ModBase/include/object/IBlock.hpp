#ifndef MODBASE_IBLOCK_HPP
#define MODBASE_IBLOCK_HPP

#include "IObject.hpp"
#include <cstdint>
#include <memory>

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace material
			{
				class IMaterial;
			}

			namespace model
			{
				class IRenderModel;
			}
		}
	}

	namespace mod
	{
		namespace object
		{
			class IBlock :
				public virtual IObject
			{
			public:
				virtual std::shared_ptr<const CubA4::render::engine::material::IMaterial> getRenderMaterial() const = 0;
				virtual std::shared_ptr<const CubA4::render::engine::model::IRenderModel> getRenderModel() const = 0;
			protected:
				explicit IBlock() = default;
				virtual ~IBlock() = default;
			};
		}
	}
}

#endif // MODBASE_IBLOCK_HPP