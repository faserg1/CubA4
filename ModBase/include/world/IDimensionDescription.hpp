#pragma once

#include <string>
#include <memory>
#include <world/IWorldGenerator.hpp>

namespace CubA4::world
{
	class IDimensionDescription
	{
	public:
		virtual std::string getId() const = 0;
		virtual std::wstring getName() const = 0;

		virtual std::shared_ptr<IWorldGenerator> getWorldGenerator() const = 0;
		// get world generator
	protected:
		explicit IDimensionDescription() = default;
		virtual ~IDimensionDescription() = default;
	private:
	};
}
