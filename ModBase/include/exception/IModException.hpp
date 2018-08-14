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
			explicit IModException() = default;
			virtual ~IModException() = default;

			virtual std::string message() const noexcept = 0;
		};
	}
}

#endif // MODEXCEPTION_HPP