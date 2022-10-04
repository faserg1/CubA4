#pragma once

#include <config/ICoreConfig.hpp>
#include <memory>
#include "./data/CoreData.hpp"

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
				std::shared_ptr<CoreData> configTree_;
				void flushConfig();
			};
		}
		
	}
}

