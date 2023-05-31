#pragma once

#include <string>

namespace CubA4::config
{
	//Пока делаем простую реализацию
	class ICoreConfig
	{
	public:
		virtual std::string getRenderEngineId() const = 0;
		virtual void setRenderEngineId(const std::string &renderEngineId) = 0;
		virtual std::string getMainFeatiresModId() const = 0;
		virtual void setMainFeaturesModId(const std::string &modId) = 0;
		virtual std::string checkFeatureModId(const std::string &feature) const = 0;
		virtual void setFeatureModId(const std::string &feature, const std::string &modId) = 0;

		virtual void reload() = 0;

		virtual ~ICoreConfig() = default;
	protected:
		explicit ICoreConfig() = default;
	};
}
