#ifndef COREBASE_ICORECONFIG_HPP
#define COREBASE_ICORECONFIG_HPP

#include <string>

namespace CubA4
{
	namespace core
	{
		namespace config
		{
			//Пока делаем простую реализацию
			class ICoreConfig
			{
			public:
				virtual std::string getRenderEngineId() const = 0;
				virtual void setRenderEngineId(const std::string &renderEngineId) = 0;
				virtual std::string getMainFeatiresModId() const = 0;
				virtual void setMainFeaturesModId(const std::string &modId) = 0;
				virtual unsigned short getWorldChunkSize() = 0;
				virtual void setWorldChunkSize(unsigned short size) = 0;

				virtual void reload() = 0;

				virtual ~ICoreConfig() = default;
			protected:
				explicit ICoreConfig() = default;
			};
		}
		
	}
}

#endif // COREBASE_ICORECONFIG_HPP