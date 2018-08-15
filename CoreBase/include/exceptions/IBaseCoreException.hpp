#ifndef IBASECOREEXCEPTION_HPP
#define IBASECOREEXCEPTION_HPP

namespace core
{
	namespace exceptions
	{
		class IBaseCoreException
		{
		public:
			virtual ~IBaseCoreException() {}
		protected:
			explicit IBaseCoreException() {}
		private:
		};
	}
}

#endif // IBASECOREEXCEPTION_HPP
