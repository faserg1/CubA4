#ifndef ICOLLISIONMODEL_HPP
#define ICOLLISIONMODEL_HPP

#include "IModel.hpp"

namespace CubA4
{
	namespace core
	{
		namespace model
		{
			class ICollisionModel :
				public virtual IModel
			{
			public:
				
			protected:
				explicit ICollisionModel() {}
				virtual ~ICollisionModel() {}
			private:
			};
		}
	}
}

#endif // ICOLLISIONMODEL_HPP
