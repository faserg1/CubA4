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
				explicit ICollisionModel() = default;
				virtual ~ICollisionModel() = default;
			private:
			};
		}
	}
}

#endif // ICOLLISIONMODEL_HPP
