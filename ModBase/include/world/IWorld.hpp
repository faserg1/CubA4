#ifndef IWOLRD_HPP
#define IWOLRD_HPP

#include <string>
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

				virtual void subscribe(IWorldSubscriber *subscriber) = 0;
				virtual void unsubscribe(IWorldSubscriber *subscriber) = 0;

				virtual std::shared_ptr<const IWorldDefinition> getWorldDefinition() const = 0;
				
				virtual void placeBlocks(std::shared_ptr<const CubA4::mod::object::IBlock> block, std::vector<BlockGlobalPos> positions) = 0;
			protected:
				explicit IWorld() = default;
			};
		}
	}
}

#endif // IWOLRD_HPP