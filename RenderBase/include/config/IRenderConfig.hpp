#ifndef IRENDERCONFIG_HPP
#define IRENDERCONFIG_HPP

#include <tuple>

namespace CubA4
{
	namespace render
	{
		namespace config
		{
			class IRenderConfig
			{
			public:
				virtual std::tuple<unsigned, unsigned> getRenderResolution(std::tuple<unsigned, unsigned> = {0, 0}) const = 0;
				virtual void setRenderResolution(std::tuple<unsigned, unsigned> res) = 0;

				virtual void reload() = 0;
			protected:
				explicit IRenderConfig() {}
				virtual ~IRenderConfig() {}
			private:
			};
		}
	}
}

#endif // IRENDERCONFIG_HPP