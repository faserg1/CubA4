#ifndef MODRUNTIMEEXCEPTION_HPP
#define MODRUNTIMEEXCEPTION_HPP

#include "IModException.hpp"

namespace CubA4
{
	namespace exception
	{
		class IModRuntimeException :
			public virtual IModException
		{
		public:
			explicit IModRuntimeException() = default;
			virtual ~IModRuntimeException() = default;
		};
	}
}

#endif // MODRUNTIMEEXCEPTION_HPP