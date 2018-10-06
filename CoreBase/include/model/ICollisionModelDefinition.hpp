#ifndef ICOLLISIONMODEL_HPP
#define ICOLLISIONMODEL_HPP

#include "IModelDefinition.hpp"

namespace CubA4
{
	namespace core
	{
		namespace model
		{
			class ICollisionModelDefinition :
				public virtual IModelDefinition
			{
			public:
				
			protected:
				explicit ICollisionModelDefinition() = default;
				virtual ~ICollisionModelDefinition() = default;
			private:
			};
		}
	}
}

#endif // ICOLLISIONMODEL_HPP
