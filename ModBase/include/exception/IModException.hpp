#ifndef MODEXCEPTION_HPP
#define MODEXCEPTION_HPP

#include <string>

namespace CubA4
{
	namespace exception
	{
		class IModException
		{
		public:
			explicit IModException() {}
			virtual ~IModException() {}

			virtual std::string message() const noexcept = 0;
		};
	}
}

#endif // MODEXCEPTION_HPP