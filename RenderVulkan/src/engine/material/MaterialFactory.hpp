#ifndef MATERIALFACTORY_HPP
#define MATERIALFACTORY_HPP

#include <memory>
#include <engine/material/IMaterialFactory.hpp>

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace material
			{
				class MaterialFactory :
					public virtual IMaterialFactory
				{
				public:
					explicit MaterialFactory();
					~MaterialFactory();

					std::shared_ptr<IMaterialBuilder> createMaterial(std::shared_ptr<const IMaterialLayout> layout) override;
				protected:
				private:
				};
			}
		}
	}
}

#endif // MATERIALFACTORY_HPP
