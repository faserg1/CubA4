#ifndef MODBASE_MODEXCEPTION_HPP
#define MODBASE_MODEXCEPTION_HPP

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

#endif // MODBASE_MODEXCEPTION_HPP