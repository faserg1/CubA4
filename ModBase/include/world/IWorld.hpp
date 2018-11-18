#ifndef IWOLRD_HPP
#define IWOLRD_HPP

#include <string>
#include <util/ISubscription.hpp>
#include "IChunk.hpp"
#include "../object/IObject.hpp"

namespace CubA4
{
	namespace mod
	{
		namespace world
		{
			class IWorldSubscriber;
			class IWorldDefinition;

			class IWorld :
				public virtual CubA4::mod::object::IObject
			{
			public:
				virtual ~IWorld() = default;

				virtual std::shared_ptr<CubA4::core::util::ISubscription> subscribe(IWorldSubscriber *subscriber) = 0;

				virtual std::shared_ptr<const IWorldDefinition> getWorldDefinition() const = 0;
				
				virtual void placeBlocks(std::shared_ptr<const CubA4::mod::object::IBlock> block, const std::vector<BlockGlobalPos> positions) = 0;
			protected:
				explicit IWorld() = default;
			};
		}
	}
}

#endif // IWOLRD_HPP