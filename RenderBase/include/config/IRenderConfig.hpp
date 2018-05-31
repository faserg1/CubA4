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
				virtual std::tuple<unsigned, unsigned> getRenderResolution() = 0;
			protected:
				explicit IRenderConfig() {}
				virtual ~IRenderConfig() {}
			private:
			};
		}
	}
}

#endif // IRENDERCONFIG_HPP
