#ifndef MATERIALMANAGER_HPP
#define MATERIALMANAGER_HPP

#include <engine/material/IMaterialManager.hpp>

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace material
			{
				class MaterialManager :
					public virtual IMaterialManager
				{
				public:
					explicit MaterialManager();
					~MaterialManager();
				protected:
				private:
				};
			}
		}
	}
}

#endif // MATERIALMANAGER_HPP
