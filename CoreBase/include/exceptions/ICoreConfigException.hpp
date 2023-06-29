#pragma once

#include <exceptions/ICoreException.hpp>
#include <string> 

namespace CubA4::exceptions
{
	enum class ConfigExceptionsSourceType : char
	{
		ReadConfigurationFile, ///< Неудавшиеся чтение файла конфигурации
		CreatureConfigurationFile, ///< Неудавшиеся создание файла конфигурации
		PreserveConfigurationFile, ///< Неудавшиеся сохрание файла конфигурации
		FailedReadConfig, ///< Неудавшиеся прочтение самого конфига
		FailedSaveConfig ///< Неудавшиеся сохранение самого конфига
	};


	class ICoreConfigException :
		public virtual ICoreException
	{
	public:
		virtual ConfigExceptionsSourceType source() = 0;
	protected:
		virtual ~ICoreConfigException() = default;
		explicit ICoreConfigException() = default;
	private:
	};
}
