#pragma once

#include <memory>
#include <vulkan/vulkan.h>
#include <vector>
#include <vulkan/pipeline/PipelineBuilderBase.hpp>
#include <config/VulkanConfigAdapter.hpp>
#include <vulkan/util/VulkanHandlerContainer.hpp>

namespace CubA4::render
{
	namespace engine
	{
		namespace material
		{
			class IShader;
		}
	}

	namespace vulkan
	{
		class Device;

		class Pipeline;
		struct PipelineInfo;

		class PipelineBuilderMaterial : public PipelineBuilderBase
		{
		public:
			explicit PipelineBuilderMaterial(std::shared_ptr<const Device> device, CubA4::render::config::VulkanConfigAdapter config);
			~PipelineBuilderMaterial();

			void addTexture();
			sVkDescriptorSetLayout getTextureLayout();
		protected:
		private:
			VkSpecializationInfo vertexShaderSpec_;
			std::vector<VkSpecializationMapEntry> vertexShaderSpecEntries_;
			std::vector<unsigned char> vertexShaderSpecData_;

			std::vector<VkPipelineColorBlendAttachmentState> colorAttachments_;

			std::vector<VkDynamicState> dynamicStates_;

			uint32_t textureCount = 0;
			sVkDescriptorSetLayout textureLayout_;
		private:
			void prepareVertexInput() override;
			void prepareInputAssembly() override;
			void prepareRasterization() override;
			void prepareMultisampling() override;
			void prepareDepthStencil() override;
			void prepareColorBlending() override;
			void prepareDynmaic() override;
			void prepareViewport() override;

			void prepareDescriptorSets() override;
			void preparePushConstants() override;
		};
	}
}