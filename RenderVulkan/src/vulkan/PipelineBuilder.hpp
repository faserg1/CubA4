#ifndef PIPELINEBUILDER_HPP
#define PIPELINEBUILDER_HPP

#include <memory>
#include <vulkan/vulkan.h>
#include <vector>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Device;

			class PipelineBuilder
			{
			public:
				explicit PipelineBuilder(std::shared_ptr<const Device> device);
				~PipelineBuilder();
			protected:
			private:
				const std::shared_ptr<const Device> device_;

				VkPipelineVertexInputStateCreateInfo vertexInputInfo_;
				std::vector<VkVertexInputBindingDescription> vertexBindingDescriptions_;
				std::vector<VkVertexInputAttributeDescription> vertexAttrDescriptions_;

				VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo_;
				VkPipelineRasterizationStateCreateInfo rasterizationInfo_;
				VkPipelineMultisampleStateCreateInfo multisampleInfo_;
				VkPipelineDepthStencilStateCreateInfo depthStencilInfo_;
				VkPipelineColorBlendStateCreateInfo colorBlendInfo_;
				VkPipelineDynamicStateCreateInfo dynamicInfo_;
			private:
				void prepareVertexInput();
				void prepareInputAssembly();
				void prepareRasterization();
				void prepareMultisampling();
				void prepareDepthStencil();
				void prepareColorBlending();
				void prepareDynamics();
				void prepareDescriptorSets();
			};
		}
	}
}

#endif // PIPELINEBUILDER_HPP
