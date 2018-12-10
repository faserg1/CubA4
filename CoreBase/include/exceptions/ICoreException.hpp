#ifndef COREBASE_ICOREEXCEPTION_HPP
#define COREBASE_ICOREEXCEPTION_HPP

namespace core
{
	namespace exceptions
	{
	
		class ICoreException
		{
		public:
			
		protected:
			virtual ~ICoreException() {}
			explicit ICoreException() {}
		private:
		};
	}
}

#endif // COREBASE_ICOREEXCEPTION_HPP
