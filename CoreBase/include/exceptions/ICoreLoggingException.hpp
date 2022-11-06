#pragma once

#include <exceptions/ICoreException.hpp>


namespace CubA4::exceptions
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
