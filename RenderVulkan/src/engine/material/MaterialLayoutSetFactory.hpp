#ifndef MATERIALLAYOUTSETFACTORY_HPP
#define MATERIALLAYOUTSETFACTORY_HPP

#include <engine/material/IMaterialLayoutSetFactory.hpp>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Device;
		}

		namespace engine
		{
			class Render;

			namespace material
			{
				class MaterialLayoutSetFactory :
					public virtual IMaterialLayoutSetFactory
				{
				public:
					explicit MaterialLayoutSetFactory(std::shared_ptr<const vulkan::Device> device, std::shared_ptr<const Render> render);
					~MaterialLayoutSetFactory();

					std::shared_ptr<IMaterialLayoutBuilder> createMaterialLayout() override;
					std::vector<std::shared_ptr<const IMaterialLayout>> build() override;
				protected:
				private:
					const std::shared_ptr<const vulkan::Device> device_;
					const std::shared_ptr<const Render> render_;
					std::vector<std::shared_ptr<IMaterialLayoutBuilder>> builders_;
				};
			}
		}
	}
}

#endif // MATERIALLAYOUTSETFACTORY_HPP
