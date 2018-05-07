#ifndef BASEOBJECT_HPP
#define BASEOBJECT_HPP

#include <string>
#include <cstdint>

namespace CubA4
{
	namespace object
	{
		class BaseObject
		{
		public:
			virtual ~BaseObject() {}

			//Получает уникальный идентификатор объекта
			virtual std::string getId() = 0;
			virtual int64_t getMappedId() = 0;
			virtual std::wstring getName() = 0;
		protected:
			explicit BaseObject() {}
		};
	}
}

#endif // BASEOBJECT_HPP