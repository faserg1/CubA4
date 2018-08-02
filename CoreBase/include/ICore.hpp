#ifndef ICORE_HPP
#define ICORE_HPP

#include <memory>

namespace CubA4
{
	namespace core
	{
		namespace system
		{
			class IStartup;
		}

		namespace config
		{
			class IFilePaths;
			class ICoreConfig;
		}

		namespace logging
		{
			class ILogger;
		}

		class ICore
		{
		public:
			//Функции, помеченные const, будут доступны везде.
			//В основном ICore передается как std::shared_ptr<const ICore>, из чего следует, что будут доступны только эти функции

			///Получает основные пути
			virtual const std::shared_ptr<const config::IFilePaths> getPaths() const = 0;
			///Получает конфигурацию приложения
			virtual std::shared_ptr<config::ICoreConfig> getConfig() const = 0;
			///Получает логгер
			virtual std::shared_ptr<logging::ILogger> getLogger() const = 0;

			//Функции, не помеченные const будут доступны только основному приложению, или там, где ICore не передается по константному указателю.
			//К примеру, через std::shared_ptr<ICore> будут доступны эти функции

			///Получает класс запуска приложения
			virtual std::shared_ptr<system::IStartup> getStartup() = 0;
			virtual void criticalException() const = 0;
		protected:
			virtual ~ICore() {}
			explicit ICore() {}
		};
	}
}

#endif // ICORE_HPP