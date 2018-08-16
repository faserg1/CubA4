#ifndef ICORECONFIGEXCEPTION_HPP
#define ICORECONFIGEXCEPTION_HPP


#include "ICoreException.hpp"
#include <string> 

namespace core
{
	namespace exceptions
	{
		enum class ConfigExceptionsSourceType : char
		{
			ReadConfigurationFile, // Неудавшиеся чтение файла конфигурации
			CreatureConfigurationFile, // Неудавшиеся создание файла конфигурации
			PreserveConfigurationFile, // Неудавшиеся сохрание файла конфигурации
			FailedReadConfig, // Неудавшиеся прочтение самого конфига
			FailedSaveConfig // Неудавшиеся сохранение самого конфига
		};


		class ICoreConfigException : public virtual ICoreException
		{
		public:
			virtual ConfigExceptionsSourceType source() = 0;
		protected:
			virtual ~ICoreConfigException() {}
			explicit ICoreConfigException() {}
		private:
		};
	}
}

#endif // ICORECONFIGEXCEPTION_HPP
