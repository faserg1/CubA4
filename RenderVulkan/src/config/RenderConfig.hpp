#ifndef RENDERVULKAN_RENDERCONFIG_HPP
#define RENDERVULKAN_RENDERCONFIG_HPP

#include <config/IRenderConfig.hpp>
#include <boost/property_tree/ptree.hpp>

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
				explicit RenderConfig(std::string configsPath);
				~RenderConfig();

				std::tuple<unsigned, unsigned> getRenderResolution(std::tuple<unsigned, unsigned> = { 0, 0 }) const override;
				void setRenderResolution(std::tuple<unsigned, unsigned> res) override;
				void reload() override;
			protected:
			private:
				std::string native_config_path_;
				std::shared_ptr<boost::property_tree::ptree> configTree_;
				void flushConfig();
			};
		}
	}
}

#endif // RENDERVULKAN_RENDERCONFIG_HPP
