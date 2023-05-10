#pragma once

#include <engine/material/IMaterialLayoutBuilder.hpp>
#include <config/VulkanConfigAdapter.hpp>
#include <vulkan/vulkan.h>
#include <vector>

#include <vulkan/pipeline/PipelineBuilderMaterial.hpp>
#include <vulkan/util/VulkanHandlerContainer.hpp>

namespace CubA4::render
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
					std::shared_ptr<const ResourceManager> resourceManager,
					CubA4::render::config::VulkanConfigAdapter config);
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
				const CubA4::render::config::VulkanConfigAdapter config_;
				const std::unique_ptr<ShaderFactory> shaderFactory_;
				CubA4::render::vulkan::PipelineBuilderMaterial pipelineBuilder_;
			};
		}
	}
}
