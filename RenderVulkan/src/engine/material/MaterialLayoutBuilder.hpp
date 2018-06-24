#ifndef MATERIALLAYOUTBUILDER_HPP
#define MATERIALLAYOUTBUILDER_HPP

#include <engine/material/IMaterialLayoutBuilder.hpp>
#include <vulkan/vulkan.h>

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
				protected:
				private:
					VkPipelineLayoutCreateInfo layoutInfo;
				};
			}
		}
	}
}

#endif // MATERIALLAYOUTBUILDER_HPP
