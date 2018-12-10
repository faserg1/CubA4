#ifndef COREBASE_ICORELOGGINGEXCEPTION_HPP
#define COREBASE_ICORELOGGINGEXCEPTION_HPP


#include "ICoreException.hpp"


namespace core
{
	namespace exceptions
	{
		enum class LoggingExceptionsSourceType : char
		{
			WrittingStreamError, ///< Ошибка при записи потока
			OpeningStreamError ///< Ошибка при открытии потока
		};


		class ICoreLoggingException :
			public virtual ICoreException
		{
		public:
			virtual LoggingExceptionsSourceType source() = 0;
		protected:
			virtual ~ICoreLoggingException() {}
			explicit ICoreLoggingException() {}
		private:
		};
	}
}

#endif // COREBASE_ICORELOGGINGEXCEPTION_HPP
