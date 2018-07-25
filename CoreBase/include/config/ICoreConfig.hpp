#ifndef ICORECONFIG_HPP
#define ICORECONFIG_HPP

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

				virtual ~ICoreConfig() {}
			protected:
				explicit ICoreConfig() {}
			};
		}
		
	}
}

#endif // ICORECONFIG_HPP