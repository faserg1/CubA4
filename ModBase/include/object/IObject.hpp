#pragma once

#include <string>
#include <cstdint>

namespace CubA4::object
{
	class IObject
	{
	public:
		using IdType = std::string;
	public:
		virtual ~IObject() = default;

		//Получает уникальный идентификатор объекта
		virtual IdType getId() const = 0;
		virtual std::wstring getName() const = 0;
	protected:
		explicit IObject() = default;
	};
}
