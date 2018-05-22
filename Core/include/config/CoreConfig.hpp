#ifndef CORECONFIG_HPP
#define CORECONFIG_HPP

#include <config/ICoreConfig.hpp>
#include <memory>
#include <boost/property_tree/ptree.hpp>

namespace CubA4
{
	namespace core
	{
		namespace config
		{
			class CoreConfig :
				public virtual ICoreConfig
			{
			public:
				explicit CoreConfig(std::string configsPath);
				~CoreConfig();

				std::string getRenderEngineId() const;
				void setRenderEngineId(const std::string &renderEngineId) override;
				std::string getMainFeatiresModId() const override;
				void setMainFeaturesModId(const std::string &modId) override;
				unsigned short getWorldChunkSize() override;
				void setWorldChunkSize(unsigned short size) override;

				void reload() override;
			private:
				std::string native_config_path_;
				std::shared_ptr<boost::property_tree::ptree> configTree_;
				void flushConfig();
			};
		}
		
	}
}

#endif// CORECONFIG_HPP
