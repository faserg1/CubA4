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
			namespace material
			{
				class MaterialLayoutSetFactory :
					public virtual IMaterialLayoutSetFactory
				{
				public:
					explicit MaterialLayoutSetFactory(std::shared_ptr<const vulkan::Device> device);
					~MaterialLayoutSetFactory();

					std::shared_ptr<IMaterialLayoutBuilder> createMaterialLayout() override;
					std::vector<std::shared_ptr<const IMaterialLayout>> build() override;
				protected:
				private:
					const std::shared_ptr<const vulkan::Device> device_;
					std::vector<std::shared_ptr<IMaterialLayoutBuilder>> builders_;
				};
			}
		}
	}
}

#endif // MATERIALLAYOUTSETFACTORY_HPP
