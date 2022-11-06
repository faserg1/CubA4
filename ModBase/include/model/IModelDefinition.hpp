#pragma once

#include <model/PrimitiveTypes.hpp>
#include <vector>
#include <string>

namespace CubA4::model
{
	class IModelDefinition
	{
	public:
		virtual const std::string &getId() const = 0;
	protected:
		explicit IModelDefinition() = default;
		virtual ~IModelDefinition() = default;
	private:
	};
}
