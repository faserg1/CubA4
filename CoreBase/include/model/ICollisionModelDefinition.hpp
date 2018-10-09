#ifndef ICOLLISIONMODELDEFINITION_HPP
#define ICOLLISIONMODELDEFINITION_HPP

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

#endif // ICOLLISIONMODELDEFINITION_HPP
