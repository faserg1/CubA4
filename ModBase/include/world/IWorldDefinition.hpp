#pragma once

#include <string>
#include <world/IDimensionDescription.hpp>
#include <functional>

namespace CubA4::world
{
	class IWorldDefinition
	{
	public:
		using DimensionDescriptionCollection = std::vector<std::reference_wrapper<const IDimensionDescription>>;

		virtual std::string getId() const = 0;
		virtual std::wstring getName() const = 0;

		virtual const DimensionDescriptionCollection &getDimensionDescriptions() const = 0;
	protected:
		explicit IWorldDefinition() = default;
		virtual ~IWorldDefinition() = default;
	private:
	};
}
