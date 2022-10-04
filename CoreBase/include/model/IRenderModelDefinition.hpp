#pragma once

#include "IModelDefinition.hpp"
#include <vector>

namespace CubA4
{
	namespace core
	{
		namespace model
		{
			class IRenderModelDefinition :
				public virtual IModelDefinition
			{
			public:
				/**
				@brief Получение списка индексов вершин для составлеия граней
				@return Кол-во индексов, [индексы грани], ...
				**/
				virtual std::vector<unsigned short> getFaceIndices() const = 0;
			protected:
				explicit IRenderModelDefinition() = default;
				virtual ~IRenderModelDefinition() = default;
			private:
			};
		}
	}
}
