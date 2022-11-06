#pragma once

#include <string>

namespace CubA4::world
{
	class IWorldDefinition
	{
	public:
		virtual std::string getId() const = 0;
		virtual std::wstring getName() const = 0;
	protected:
		explicit IWorldDefinition() = default;
		virtual ~IWorldDefinition() = default;
	private:
	};
}
