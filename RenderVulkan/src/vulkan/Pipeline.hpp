#ifndef PIPELINE_HPP
#define PIPELINE_HPP

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

			struct PipelineInfo
			{
				VkPipeline pipeline;
				VkPipelineLayout layout;
				VkPipelineBindPoint bindPoint;

				std::vector<VkDescriptorSetLayout> descriptorSetLayouts;
				std::vector<std::shared_ptr<const engine::material::IShader>> shaders;
			};

			class Pipeline
			{
			public:
				explicit Pipeline(std::shared_ptr<const Device> device, PipelineInfo info);
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

				std::vector<VkDescriptorSetLayout> descriptorSetLayouts_;
				std::vector<std::shared_ptr<const engine::material::IShader>> shaders_;
			};
		}
	}
}

#endif // PIPELINE_HPP
