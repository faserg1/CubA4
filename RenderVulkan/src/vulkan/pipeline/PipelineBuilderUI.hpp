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

		class PipelineBuilderUI : public PipelineBuilderBase
		{
		public:
			explicit PipelineBuilderUI(std::shared_ptr<const Device> device, CubA4::render::config::VulkanConfigAdapter config);
			~PipelineBuilderUI();

			sVkDescriptorSetLayout getTextureLayout();
		protected:
		private:
			VkSpecializationInfo vertexShaderSpec_;
			std::vector<VkSpecializationMapEntry> vertexShaderSpecEntries_;
			std::vector<unsigned char> vertexShaderSpecData_;

			std::vector<VkPipelineColorBlendAttachmentState> colorAttachments_;

			std::vector<VkViewport> viewports_;
			std::vector<VkRect2D> scissors_;
			std::vector<VkDynamicState> dynamicStates_;

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