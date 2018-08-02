#ifndef ISHAPEMODEL_HPP
#define ISHAPEMODEL_HPP

#include "IModel.hpp"

namespace CubA4
{
	namespace core
	{
		namespace model
		{
			class IShapeModel :
				public virtual IModel
			{
			public:
				
			protected:
				explicit IShapeModel() {}
				virtual ~IShapeModel() {}
			private:
			};
		}
	}
}

#endif // ISHAPEMODEL_HPP
