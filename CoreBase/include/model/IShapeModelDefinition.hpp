#ifndef COREBASE_ISHAPEMODELDEFINITION_HPP
#define COREBASE_ISHAPEMODELDEFINITION_HPP

#include "IModelDefinition.hpp"

namespace CubA4
{
	namespace core
	{
		namespace model
		{
			class IShapeModelDefinition :
				public virtual IModelDefinition
			{
			public:
				
			protected:
				explicit IShapeModelDefinition() = default;
				virtual ~IShapeModelDefinition() = default;
			private:
			};
		}
	}
}

#endif // COREBASE_ISHAPEMODELDEFINITION_HPP
