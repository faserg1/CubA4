#ifndef MODBASE_IWOLRD_HPP
#define MODBASE_IWOLRD_HPP

#include <string>
#include <vector>
#include "IChunk.hpp"
#include "../object/IObject.hpp"

namespace CubA4
{
	namespace core
	{
		namespace util
		{
			class ISubscription;
		}
	}

	namespace mod
	{
		namespace object
		{
			class IBlock;
		}

		namespace world
		{
			class IWorldSubscriber;
			class IWorldDefinition;

			class IChunk;

			class IWorld :
				public virtual CubA4::mod::object::IObject
			{
			public:
				virtual ~IWorld() = default;

				virtual std::unique_ptr<CubA4::core::util::ISubscription> subscribe(IWorldSubscriber *subscriber) const = 0;

				// TODO: [OOKAMI] Test the chunk range feature. Delete function later
				virtual void test(std::shared_ptr<const object::IBlock> block) = 0;

				virtual std::shared_ptr<const IWorldDefinition> getWorldDefinition() const = 0;
				virtual std::vector<std::shared_ptr<const IChunk>> getChunks() const = 0;
			protected:
				explicit IWorld() = default;
			};
		}
	}
}

#endif // MODBASE_IWOLRD_HPP
