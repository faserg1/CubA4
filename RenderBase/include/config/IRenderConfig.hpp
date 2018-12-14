#ifndef RENDERBASE_IRENDERCONFIG_HPP
#define RENDERBASE_IRENDERCONFIG_HPP

#include <tuple>
#include <string>

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

				virtual std::string getPresentMethod(std::string = {}) const = 0;
				virtual void setPresentMethod(std::string method) = 0;

				virtual void reload() = 0;
			protected:
				explicit IRenderConfig() = default;
				virtual ~IRenderConfig() = default;
			private:
			};
		}
	}
}

#endif // RENDERBASE_IRENDERCONFIG_HPP
