#ifndef IRENDERMODEL_HPP
#define IRENDERMODEL_HPP

#include "IModel.hpp"

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
				
			protected:
				explicit IRenderModel() {}
				virtual ~IRenderModel() {}
			private:
			};
		}
	}
}

#endif // IRENDERMODEL_HPP
