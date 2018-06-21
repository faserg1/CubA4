#ifndef STANDARDPIPELINE_HPP
#define STANDARDPIPELINE_HPP

#include "BasePipeline.hpp"

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			namespace pipeline
			{
				class StandardPipeline :
					public BasePipeline
				{
				public:
					static std::shared_ptr<StandardPipeline> create(std::shared_ptr<VulkanDevice> device);
				protected:
					explicit StandardPipeline(std::shared_ptr<VulkanDevice> device);
					~StandardPipeline();

					virtual VkPipelineLayoutCreateInfo &getPipelineLayoutCreateInfo() const override;
					virtual VkGraphicsPipelineCreateInfo &getPipelineCreateInfo() const override;
				private:
				};
			}
		}
	}
}

#endif // STANDARDPIPELINE_HPP
