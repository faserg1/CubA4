#include <vulkan/FramebuffersBuilder.hpp>
using namespace CubA4::render::vulkan;
using namespace CubA4::render::engine::memory;

constexpr const size_t MemoryManagerBlockSize = 1024 * 1024 * 256; // 128MB
// extern do not work =(
VkSampleCountFlagBits aaSamples = VK_SAMPLE_COUNT_2_BIT;

FramebuffersBuilder::FramebuffersBuilder(std::shared_ptr<const vulkan::Device> device, CommandPool &commandPool, CubA4::render::config::VulkanConfigAdapter config) :
    device_(device), config_(config), commandPool_(commandPool), allocator_(device)
{
	
}

FramebuffersBuilder::~FramebuffersBuilder()
{
	
}

uint32_t FramebuffersBuilder::addAttachmentInfo(const AttachmentInfo &info)
{
	auto idx = attachmentInfos_.size();
	attachmentInfos_.push_back(info);
	return static_cast<uint32_t>(idx);
}

uint32_t FramebuffersBuilder::getAttachmentsCount() const
{
	return static_cast<uint32_t>(attachmentInfos_.size());
}

std::vector<std::shared_ptr<Framebuffer>> FramebuffersBuilder::createFramebuffers(std::shared_ptr<const Swapchain> swapchain, std::shared_ptr<const vulkan::RenderPass> renderPass)
{
    uint32_t imgCount = swapchain->getImageCount();
	std::vector<VkImage> images = swapchain->getImages();
    std::vector<VkCommandBuffer> cmdBuffers(imgCount);
    std::vector<std::shared_ptr<Framebuffer>> framebuffers(imgCount);

    commandPool_.allocate(imgCount, cmdBuffers.data());
    auto resolution = swapchain->getResolution();
    auto format = swapchain->getFormat();
    auto vkRenderPass = renderPass->getRenderPass();
    for (size_t idx = 0; idx < imgCount; idx++)
    {
		std::vector<std::shared_ptr<FramebufferImage>> attachments;
		attachments.reserve(attachmentInfos_.size());

		for (const auto &info : attachmentInfos_)
		{
			if (info.type == AttachmentInfo::Type::Present) {
				attachments.push_back(std::make_shared<FramebufferImage>(device_, images[idx], format, resolution, info.aspect));
				continue;
			}

			std::shared_ptr<FramebufferImage> image;
			VkFormat currentFormat;
			VkImageUsageFlags currentUsage;

			switch (info.type)
				{
				case AttachmentInfo::Type::Color:
					currentFormat = format;
					currentUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
					break;
				case AttachmentInfo::Type::Depth:
					currentFormat = VK_FORMAT_D32_SFLOAT_S8_UINT;
					currentUsage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
					break;
				default:
					//TODO: [OOKAMI] Exception, etc
					break;
				}

			if (info.external.size() && info.type != AttachmentInfo::Type::Present) {
				image = std::make_shared<FramebufferImage>(device_, info.external[idx], currentFormat, resolution, info.aspect);
			}
			else {
				image = createImageWithMemory(currentFormat, resolution, currentUsage | info.additionalUsage, info.aspect, info.enableAA);
			}

			attachments.push_back(image);
		}

        framebuffers[idx] = std::make_shared<Framebuffer>(device_, attachments, vkRenderPass, cmdBuffers[idx]);
    }
	
    return std::move(framebuffers);
}

std::shared_ptr<FramebufferImage> FramebuffersBuilder::createImageWithMemory(VkFormat format, VkExtent2D resolution,
	VkImageUsageFlags usage, VkImageAspectFlags aspectFlags, bool aa, VkImageLayout initLayout)
{
    VkImage image;

    VkImageCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    info.format = format;
    info.imageType = VK_IMAGE_TYPE_2D;
    info.initialLayout = initLayout;
	if (aa)
    	info.samples = config_.getAntialiasing();
	else
		info.samples = VK_SAMPLE_COUNT_1_BIT;
    info.usage = usage;
    // TODO: [OOKAMI] Get from capabilities
    info.tiling = VK_IMAGE_TILING_OPTIMAL;
    info.extent.width = resolution.width;
    info.extent.height = resolution.height;
    info.extent.depth = 1;
    info.arrayLayers = 1;
    info.mipLevels = 1;
    
    if (vkCreateImage(device_->getDevice(), &info, nullptr, &image) != VK_SUCCESS)
    {
        //TODO: [OOKAMI] Exception, etc
        return {};
    }

    VkMemoryRequirements memReq = {};
	vkGetImageMemoryRequirements(device_->getDevice(), image, &memReq);

    auto memory = allocator_.allocateAndBind(image, MemoryAllocationPrefered::Device);
    if (!memory)
    {
        vkDestroyImage(device_->getDevice(), image, nullptr);
        //TODO: [OOKAMI] Exception, etc
        return {};
    }

    return std::make_shared<FramebufferImage>(device_, image, format, resolution, aspectFlags, memory);
}