#ifndef ENVIRONMENTBUILDERDATA_HPP
#define ENVIRONMENTBUILDERDATA_HPP

#include <memory>
#include <map>
#include "IdentityMap.hpp"

namespace CubA4
{
	namespace mod
	{
		namespace object
		{
			class IBlock;
			class IEntity;
			class IItem;
		}

		namespace world
		{
			class IWorld;
		}
	}

	namespace render
	{
		class IRenderInfo;

		namespace engine
		{
			class IRenderManager;
		}
	}

	namespace core
	{
		namespace system
		{
			class EnvironmentBuilderData
			{
				friend class EnvironmentBuilder;
			public:
				explicit EnvironmentBuilderData(
					std::shared_ptr<CubA4::render::engine::IRenderManager> renderManager,
					const CubA4::render::IRenderInfo &renderInfo);
				~EnvironmentBuilderData();
			protected:
			private:
				const CubA4::render::IRenderInfo &renderInfo_;
				const std::shared_ptr<CubA4::render::engine::IRenderManager> renderManager_;
				IdentityMap identityMap_;
				std::map<int64_t, const std::shared_ptr<const CubA4::mod::object::IBlock>> blocks_;
			};
		}
	}
}

#endif // ENVIRONMENTBUILDERDATA_HPP
