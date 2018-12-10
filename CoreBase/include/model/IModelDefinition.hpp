#ifndef COREBASE_IMODELDEFINITION_HPP
#define COREBASE_IMODELDEFINITION_HPP

#include <vector>
#include <string>

namespace CubA4
{
	namespace core
	{
		namespace model
		{
			/// Вершина
			struct Vertex
			{
				float x;
				float y;
				float z;
			};

			class IModelDefinition
			{
			public:
				virtual std::string getId() const = 0;
				virtual std::vector<Vertex> getVertices() const = 0;
			protected:
				explicit IModelDefinition() = default;
				virtual ~IModelDefinition() = default;
			private:
			};
		}
	}
}

#endif // COREBASE_IMODELDEFINITION_HPP
