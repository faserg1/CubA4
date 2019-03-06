#ifndef RENDERVULKAN_MATERIALLAYOUTBUILDER_HPP
#define RENDERVULKAN_MATERIALLAYOUTBUILDER_HPP

#include <engine/material/IMaterialLayoutBuilder.hpp>
#include <vulkan/vulkan.h>
#include <vector>

#include "../../vulkan/PipelineBuilder.hpp"
#include "../../vulkan/util/VulkanHandlerContainer.hpp"

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
			class Render;
			class ResourceManager;

			namespace material
			{
				class ShaderFactory;

				class MaterialLayoutBuilder :
					public virtual IMaterialLayoutBuilder
				{
				public:
					explicit MaterialLayoutBuilder(std::shared_ptr<const vulkan::Device> device,
						std::shared_ptr<const Render> render,
						std::shared_ptr<const ResourceManager> resourceManager);
					~MaterialLayoutBuilder();

					void setType(MaterialType type) override;
					void addTexture() override;
					vulkan::sVkDescriptorSetLayout getTextureLayout();

					/** \brief Подготовка MaterialLayout к созданию
					* \param[out] pipelineCreateInfo 
					*/
					void prepare(VkGraphicsPipelineCreateInfo &pipelineCreateInfo);
					void fillPipelineInfo(vulkan::PipelineInfo &pipelineInfo) const;
				protected:
				private:
					const std::shared_ptr<const vulkan::Device> device_;
					const std::shared_ptr<const Render> render_;
					const std::shared_ptr<const ResourceManager> resourceManager_;
					const std::unique_ptr<ShaderFactory> shaderFactory_;
					CubA4::render::vulkan::PipelineBuilder pipelineBuilder_;
				};
			}
		}
	}
}

#endif // RENDERVULKAN_MATERIALLAYOUTBUILDER_HPP
