#pragma once

#include <memory>
#include <vulkan/vulkan.h>
#include <vector>
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

		struct PipelineInfo
		{
			VkPipeline pipeline;
			VkPipelineLayout layout;
			VkPipelineBindPoint bindPoint;

			std::vector<sVkDescriptorSetLayout> descriptorSetLayouts;
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

			std::vector<sVkDescriptorSetLayout> descriptorSetLayouts_;
			std::vector<std::shared_ptr<const engine::material::IShader>> shaders_;
		};
	}
}
