#ifndef MATERIALLAYOUTBUILDER_HPP
#define MATERIALLAYOUTBUILDER_HPP

#include <engine/material/IMaterialLayoutBuilder.hpp>
#include <vulkan/vulkan.h>
#include <vector>

#include "../../vulkan/PipelineBuilder.hpp"

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Device;
			struct PipelineInfo;
		}

		namespace engine
		{
			namespace material
			{
				class MaterialLayoutBuilder :
					public virtual IMaterialLayoutBuilder
				{
				public:
					explicit MaterialLayoutBuilder(std::shared_ptr<const vulkan::Device> device);
					~MaterialLayoutBuilder();

					void useShader(std::shared_ptr<const IShader> shader) override;

					/** \brief Подготовка MaterialLayout к созданию
					* \param[out] pipelineCreateInfo 
					*/
					void prepare(VkGraphicsPipelineCreateInfo &pipelineCreateInfo);
					void fillPipelineInfo(vulkan::PipelineInfo &pipelineInfo) const;
				protected:
				private:
					const std::shared_ptr<const vulkan::Device> device_;
					CubA4::render::vulkan::PipelineBuilder pipelineBuilder_;
				};
			}
		}
	}
}

#endif // MATERIALLAYOUTBUILDER_HPP
