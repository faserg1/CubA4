#ifndef MODBASE_IOBJECT_HPP
#define MODBASE_IOBJECT_HPP

#include <string>
#include <cstdint>

namespace CubA4
{
	namespace mod
	{
		namespace object
		{
			class IObject
			{
			public:
				virtual ~IObject() = default;

				//Получает уникальный идентификатор объекта
				virtual std::string getId() const = 0;
				virtual std::wstring getName() const = 0;
			protected:
				explicit IObject() = default;
			};
		}
	}
}

#endif // MODBASE_IOBJECT_HPP