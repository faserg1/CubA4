#ifndef MODBASE_MODLOADEXCEPTION_HPP
#define MODBASE_MODLOADEXCEPTION_HPP

#include "IModException.hpp"

namespace CubA4
{
	namespace exception
	{
		enum class ModState : char;

		class IModLoadException :
			public virtual IModException 
		{
		public:
			explicit IModLoadException() = default;
			virtual ~IModLoadException() = default;

			/// Возвращает этап, а котором произошла ошибка
			virtual ModState getErrorState() const noexcept = 0;
		};
	}
}

#endif // MODBASE_MODLOADEXCEPTION_HPP