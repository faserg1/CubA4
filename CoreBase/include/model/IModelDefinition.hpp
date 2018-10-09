#ifndef IMODELDEFINITION_HPP
#define IMODELDEFINITION_HPP

#include <vector>

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
				virtual std::vector<Vertex> getVertices() const = 0;
			protected:
				explicit IModelDefinition() = default;
				virtual ~IModelDefinition() = default;
			private:
			};
		}
	}
}

#endif // IMODELDEFINITION_HPP
