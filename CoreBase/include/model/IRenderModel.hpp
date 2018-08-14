#ifndef IRENDERMODEL_HPP
#define IRENDERMODEL_HPP

#include "IModel.hpp"
#include <vector>

namespace CubA4
{
	namespace core
	{
		namespace model
		{
			class IRenderModel :
				public virtual IModel
			{
			public:
				/**
				@brief Получение списка индексов вершин для составлеия граней
				@return Кол-во индексов, [индексы грани], ...
				**/
				virtual std::vector<unsigned short> getFaceIndices() const = 0;
			protected:
				explicit IRenderModel() {}
				virtual ~IRenderModel() {}
			private:
			};
		}
	}
}

#endif // IRENDERMODEL_HPP
