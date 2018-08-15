#ifndef ICORELOGGINGEXCEPTION_HPP
#define ICORELOGGINGEXCEPTION_HPP


#include "ICoreException.hpp"


namespace core
{
	namespace exceptions
	{
		class ICoreLoggingException : public virtual ICoreException
		{
		public:
			
		protected:
			virtual ~ICoreLoggingException() {}
			explicit ICoreLoggingException() {}
		private:
		};
	}
}

#endif // ICORELOGGINGEXCEPTION_HPP
