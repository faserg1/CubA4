#ifndef RENDERVULKAN_PIPELINEBUILDER_HPP
#define RENDERVULKAN_PIPELINEBUILDER_HPP

#include <memory>
#include <vulkan/vulkan.h>
#include <vector>
#include "util/VulkanHandlerContainer.hpp"

namespace CubA4
{
	namespace render
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

			class PipelineBuilder
			{
			public:
				explicit PipelineBuilder(std::shared_ptr<const Device> device);
				~PipelineBuilder();

				void useShader(std::shared_ptr<const engine::material::IShader> shader);
				void addBuiltInDescriptorSetLayout(sVkDescriptorSetLayout builtInLayout);

				VkGraphicsPipelineCreateInfo build();
				void fillPipelineInfo(PipelineInfo &pipelineInfo) const;
			protected:
			private:
				const std::shared_ptr<const Device> device_;
				VkPipelineLayout pipelineLayout_;

				std::vector<std::shared_ptr<const engine::material::IShader>> shaders_;

				VkPipelineVertexInputStateCreateInfo vertexInputInfo_;
				std::vector<VkVertexInputBindingDescription> vertexBindingDescriptions_;
				std::vector<VkVertexInputAttributeDescription> vertexAttrDescriptions_;

				VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo_;
				VkPipelineRasterizationStateCreateInfo rasterizationInfo_;
				VkPipelineMultisampleStateCreateInfo multisampleInfo_;
				VkPipelineDepthStencilStateCreateInfo depthStencilInfo_;
				VkPipelineDynamicStateCreateInfo dynamicStateInfo_;
				VkPipelineViewportStateCreateInfo viewportStateInfo_;

				VkSpecializationInfo vertexShaderSpec_;
				std::vector<VkSpecializationMapEntry> vertexShaderSpecEntries_;
				std::vector<unsigned char> vertexShaderSpecData_;

				std::vector<VkPipelineColorBlendAttachmentState> colorAttachments_;
				VkPipelineColorBlendStateCreateInfo colorBlendInfo_;

				std::vector<VkViewport> viewports_;
				std::vector<VkRect2D> scissors_;
				std::vector<VkDynamicState> dynamicStates_;
				std::vector<sVkDescriptorSetLayout> descriptorSetLayouts_;
				std::vector<VkPushConstantRange> pushConstantsRanges_;
				std::vector<VkPipelineShaderStageCreateInfo> stages_;
			private:
				void prepareStages();
				void prepareVertexInput();
				void prepareInputAssembly();
				void prepareRasterization();
				void prepareMultisampling();
				void prepareDepthStencil();
				void prepareColorBlending();
				void prepareDynmaic();
				void prepareViewport();

				void prepareDescriptorSets();
				void preparePushConstants();
			};
		}
	}
}

#endif // RENDERVULKAN_PIPELINEBUILDER_HPP
