#ifndef IMODEL_HPP
#define IMODEL_HPP

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

			class IModel
			{
			public:
				virtual std::vector<Vertex> getVertices() const = 0;
			protected:
				explicit IModel() = default;
				virtual ~IModel() = default;
			private:
			};
		}
	}
}

#endif // IMODEL_HPP
