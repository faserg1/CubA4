#ifndef RENDERVULKAN_MATERIALBUILDER_HPP
#define RENDERVULKAN_MATERIALBUILDER_HPP

#include <memory>
#include <engine/material/IMaterialBuilder.hpp>

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace material
			{
				class IMaterialLayout;

				class MaterialBuilder :
					public virtual IMaterialBuilder
				{
				public:
					explicit MaterialBuilder(std::shared_ptr<const IMaterialLayout> layout);
					~MaterialBuilder();

					std::shared_ptr<const IMaterial> build() override;
				protected:
				private:
					std::shared_ptr<const IMaterialLayout> layout_;
				};
			}
		}
	}
}

#endif // RENDERVULKAN_MATERIALBUILDER_HPP
