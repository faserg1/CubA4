#ifndef RENDERCONFIG_HPP
#define RENDERCONFIG_HPP

#include <config/IRenderConfig.hpp>

namespace CubA4
{
	namespace render
	{
		namespace config
		{
			class RenderConfig :
				public virtual IRenderConfig
			{
			public:
				explicit RenderConfig();
				~RenderConfig();

				std::tuple<unsigned, unsigned> getRenderResolution() override;
			protected:
			private:
			};
		}
	}
}

#endif // RENDERCONFIG_HPP
