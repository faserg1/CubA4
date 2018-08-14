#ifndef PIPELINE_HPP
#define PIPELINE_HPP

#include <memory>
#include <vulkan/vulkan.h>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Device;

			class Pipeline
			{
			public:
				explicit Pipeline(std::shared_ptr<const Device> device, VkPipeline pipeline, VkPipelineLayout layout, VkPipelineBindPoint bindPoint);
				~Pipeline();

				void bind(VkCommandBuffer cmdBuf) const;
				VkPipeline getPipeline() const;
				VkPipelineLayout getLayout() const;
				VkPipelineBindPoint getBindPoint() const;
			protected:
			private:
				const std::shared_ptr<const Device> device_;
				const VkPipeline pipeline_;
				const VkPipelineLayout layout_;
				const VkPipelineBindPoint bindPoint_;
			};
		}
	}
}

#endif // PIPELINE_HPP
