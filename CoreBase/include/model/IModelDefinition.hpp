#pragma once

#include <model/PrimitiveTypes.hpp>
#include <vector>
#include <string>

namespace CubA4
{
	namespace core
	{
		namespace model
		{
			class IModelDefinition
			{
			public:
				virtual std::string getId() const = 0;
				virtual std::vector<Vertex> getVertices() const = 0;
				virtual std::vector<UVWCoords> getUVWCoords() const = 0;
			protected:
				explicit IModelDefinition() = default;
				virtual ~IModelDefinition() = default;
			private:
			};
		}
	}
}
