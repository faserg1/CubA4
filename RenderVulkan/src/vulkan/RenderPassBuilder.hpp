#pragma once

#include <memory>
#include <vector>
#include <config/VulkanConfigAdapter.hpp>

namespace CubA4::render::vulkan
{
	enum class LoadOp
	{
		DontCare,
		Clear,
		Load
	};
	enum class StoreOp
	{
		DontCare,
		Store
	};

	class Device;
	class RenderPass;
	class Swapchain;

	class RenderPassBuilder
	{
	public:
		explicit RenderPassBuilder(std::shared_ptr<const Device> device, CubA4::render::config::VulkanConfigAdapter config);
		~RenderPassBuilder();

		std::shared_ptr<RenderPass> build();

		uint32_t addDescription(VkFormat format, VkImageLayout finalLayout, bool antialiasing, LoadOp loadOp, StoreOp storeOp);
		void addColorReference(uint32_t subpassIndex, uint32_t idxColor, VkImageLayout layoutColor, uint32_t idxDepth, VkImageLayout layoutDepth, uint32_t idxResolve, VkImageLayout layoutResolve);
		uint32_t addSubpass();		
	protected:
	private:
		const std::shared_ptr<const Device> device_;
		const CubA4::render::config::VulkanConfigAdapter config_;

		std::vector<VkAttachmentDescription> attachments_;
		
		struct SubpassDescription
		{
			VkSubpassDescription *desc;
			struct {
				std::vector<VkAttachmentReference> color;
				std::vector<VkAttachmentReference> depth;
				std::vector<VkAttachmentReference> resolve;
			} referencesColor_;
		};
	
		std::vector<SubpassDescription> subpasses_;
		std::vector<VkSubpassDescription> subpassesDesc_;
	};
}
