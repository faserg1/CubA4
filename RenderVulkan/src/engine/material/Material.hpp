#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <memory>
#include <engine/material/IMaterial.hpp>

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace material
			{
				class MaterialLayout;

				class Material :
					public virtual IMaterial
				{
				public:
					explicit Material(std::shared_ptr<const MaterialLayout> layout);
					~Material();

					std::shared_ptr<const MaterialLayout> getLayout() const;
				protected:
				private:
					const std::shared_ptr<const MaterialLayout> layout_;
				};
			}
		}
	}
}

#endif // MATERIAL_HPP
