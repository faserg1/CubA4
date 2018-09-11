#ifndef PIPELINEBUILDER_HPP
#define PIPELINEBUILDER_HPP

#include <memory>
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

				std::vector<VkPipelineColorBlendAttachmentState> colorAttachments_;
				VkPipelineColorBlendStateCreateInfo colorBlendInfo_;
				std::vector<VkViewport> viewports_;
				std::vector<VkRect2D> scissors_;

				std::vector<VkDescriptorSetLayout> descriptorSetLayouts_;
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

#endif // PIPELINEBUILDER_HPP
