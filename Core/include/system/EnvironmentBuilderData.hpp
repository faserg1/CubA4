#ifndef ENVIRONMENTBUILDERDATA_HPP
#define ENVIRONMENTBUILDERDATA_HPP

#include <memory>

namespace CubA4
{
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
			};
		}
	}
}

#endif // ENVIRONMENTBUILDERDATA_HPP
