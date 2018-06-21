#ifndef BASEPIPELINE_HPP
#define BASEPIPELINE_HPP

#include <vulkan/vulkan.h>
#include <memory>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class VulkanDevice;

			namespace pipeline
			{
				class BasePipeline
				{
				public:
					VkPipeline getPipeline() const;
					VkPipelineLayout getPipelineLayout() const;
				protected:
					explicit BasePipeline(std::shared_ptr<VulkanDevice> device);
					~BasePipeline();

					void init();
					void destroy();

					virtual VkPipelineLayoutCreateInfo &getPipelineLayoutCreateInfo() const = 0;
					virtual VkGraphicsPipelineCreateInfo &getPipelineCreateInfo() const = 0;
				private:
					std::shared_ptr<VulkanDevice> device_;
					VkPipeline pipeline_;
					VkPipelineLayout pipelineLayout_;
				};
			}
		}
	}
}

#endif // BASEPIPELINE_HPP
