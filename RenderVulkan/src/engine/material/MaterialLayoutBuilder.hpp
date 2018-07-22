#ifndef MATERIALLAYOUTBUILDER_HPP
#define MATERIALLAYOUTBUILDER_HPP

#include <engine/material/IMaterialLayoutBuilder.hpp>
#include <vulkan/vulkan.h>
#include <vector>

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace material
			{
				class MaterialLayoutBuilder :
					public virtual IMaterialLayoutBuilder
				{
				public:
					explicit MaterialLayoutBuilder();
					~MaterialLayoutBuilder();

					void setTransparentMode(bool transparent = true) override;

					void prepare();
					VkDescriptorSetLayoutCreateInfo &getDescriptorLayoutInfo();
				protected:
					bool transparentMode_;
				private:
					VkDescriptorSetLayoutCreateInfo descriptorLayoutInfo_;
					std::vector<VkDescriptorSetLayoutBinding> bindings_;

					void fillStartInfo();
				};
			}
		}
	}
}

#endif // MATERIALLAYOUTBUILDER_HPP
