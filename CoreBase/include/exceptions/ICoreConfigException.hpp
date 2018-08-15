#ifndef ICORECONFIGEXCEPTION_HPP
#define ICORECONFIGEXCEPTION_HPP


#include "ICoreException.hpp"


namespace core
{
	namespace exceptions
	{
		class ICoreConfigException : public virtual ICoreException
		{
		public:
			
		protected:
			virtual ~ICoreConfigException() {}
			explicit ICoreConfigException() {}
		private:
		};
	}
}

#endif // ICORECONFIGEXCEPTION_HPP
