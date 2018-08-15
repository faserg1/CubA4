#ifndef IOBJECT_HPP
#define IOBJECT_HPP

#include <string>
#include <cstdint>

namespace CubA4
{
	namespace object
	{
		class IObject
		{
		public:
			virtual ~IObject() = default;

			//Получает уникальный идентификатор объекта
			virtual std::string getId() = 0;
			virtual int64_t getMappedId() = 0;
			virtual std::wstring getName() = 0;
		protected:
			explicit IObject() = default;
		};
	}
}

#endif // IOBJECT_HPP