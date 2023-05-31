#pragma once

#include <config/ICoreConfig.hpp>
#include <memory>
#include "./data/CoreData.hpp"

namespace CubA4:: config
{
	class CoreConfig :
		public virtual ICoreConfig
	{
	public:
		explicit CoreConfig(std::string configsPath);
		~CoreConfig();

		std::string getRenderEngineId() const override;
		void setRenderEngineId(const std::string &renderEngineId) override;
		std::string getMainFeatiresModId() const override;
		void setMainFeaturesModId(const std::string &modId) override;
		std::string checkFeatureModId(const std::string &feature) const override;
		void setFeatureModId(const std::string &feature, const std::string &modId) override;

		void reload() override;
	private:
		std::string native_config_path_;
		std::shared_ptr<CoreData> configTree_;
		void flushConfig();
	};
}
