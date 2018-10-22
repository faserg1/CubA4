#ifndef IBLOCK_HPP
#define IBLOCK_HPP

#include "IObject.hpp"
#include <cstdint>
#include <memory>

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
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
				virtual ~IBlock() = default;
				virtual std::shared_ptr<const CubA4::render::engine::model::IRenderModel> getRenderModel() const = 0;
			protected:
				explicit IBlock() = default;
			};
		}
	}
}

#endif // IBLOCK_HPP