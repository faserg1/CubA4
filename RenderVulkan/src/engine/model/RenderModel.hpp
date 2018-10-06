#ifndef RENDERMODEL_HPP
#define RENDERMODEL_HPP

#include <engine/model/IRenderModel.hpp>

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace model
			{
				class RenderModel : 
					public virtual IRenderModel
				{
				public:
					explicit RenderModel();
					~RenderModel();
				protected:
				private:
				};
			}
		}
	}
}

#endif // RENDERMODEL_HPP
