#ifndef ICOREEXCEPTION_HPP
#define ICOREEXCEPTION_HPP

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

#endif // ICOREEXCEPTION_HPP
