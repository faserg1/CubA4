#pragma once

#include <memory>
#include <vector>
#include <config/VulkanConfigAdapter.hpp>
#include <vulkan/util/VulkanPNext.hpp>

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

	class RenderPassBuilder :
		public CubA4::render::vulkan::util::VulkanPNextContainer
	{
	public:
		explicit RenderPassBuilder(std::shared_ptr<const Device> device, CubA4::render::config::VulkanConfigAdapter config);
		~RenderPassBuilder();

		std::shared_ptr<RenderPass> build();

		uint32_t addDescription(VkFormat format, VkImageLayout finalLayout, bool antialiasing, LoadOp loadOp, StoreOp storeOp, VkImageLayout initLayout = VK_IMAGE_LAYOUT_UNDEFINED);
		void addColorReference(uint32_t subpassIndex, uint32_t idxColor, VkImageLayout layoutColor, uint32_t idxDepth, VkImageLayout layoutDepth, uint32_t idxResolve, VkImageLayout layoutResolve);
		VkAttachmentReference2 *addExternalColorReference(uint32_t subpassTo, const VkAttachmentReference2 &reference);
		uint32_t addSubpass();
		uint32_t subpassCount() const;	
		void addDependency(VkSubpassDependency2 dependency);

		template <class TypeNext>
		void *addSubpassDescNext(uint32_t subpassTo, TypeNext next)
		{
			return addPNext(next, &subpassesDesc_[subpassTo]);
		}
	private:
		const std::shared_ptr<const Device> device_;
		const CubA4::render::config::VulkanConfigAdapter config_;

		std::vector<VkAttachmentDescription2> attachments_;
		std::vector<VkSubpassDependency2> deps_;
		
		struct SubpassDescription
		{
			VkSubpassDescription2 *desc;
			struct {
				std::vector<VkAttachmentReference2> color;
				std::vector<VkAttachmentReference2> depth;
				std::vector<VkAttachmentReference2> resolve;
				std::vector<std::unique_ptr<VkAttachmentReference2>> external;
			} referencesColor_;
		};
	
		std::vector<SubpassDescription> subpasses_;
		std::vector<VkSubpassDescription2> subpassesDesc_;
	};
}
