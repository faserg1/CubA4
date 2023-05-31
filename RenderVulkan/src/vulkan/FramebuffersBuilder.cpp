#include <vulkan/FramebuffersBuilder.hpp>
using namespace CubA4::render::vulkan;
using namespace CubA4::render::engine::memory;

constexpr const size_t MemoryManagerBlockSize = 1024 * 1024 * 256; // 128MB
// extern do not work =(
VkSampleCountFlagBits aaSamples = VK_SAMPLE_COUNT_2_BIT;

FramebuffersBuilder::FramebuffersBuilder(std::shared_ptr<const vulkan::Device> device, CubA4::render::config::VulkanConfigAdapter config) :
    device_(device), config_(config), allocator_(device),
    commandPool_(device, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT)
{
	
}

FramebuffersBuilder::~FramebuffersBuilder()
{
	
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
        auto framebufferImage = createImageWithMemory(format, resolution, VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, VK_IMAGE_ASPECT_COLOR_BIT);
        auto presentImage = std::make_shared<FramebufferImage>(device_, images[idx], format, resolution, VK_IMAGE_ASPECT_COLOR_BIT);
        
        auto depthImage = createImageWithMemory(VK_FORMAT_D32_SFLOAT_S8_UINT, resolution, VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT | VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_IMAGE_ASPECT_DEPTH_BIT);

        auto attachments = std::vector{framebufferImage, depthImage, presentImage};

        framebuffers[idx] = std::make_shared<Framebuffer>(device_, attachments, vkRenderPass, cmdBuffers[idx]);
    }
	
    return std::move(framebuffers);
}

std::shared_ptr<FramebufferImage> FramebuffersBuilder::createImageWithMemory(VkFormat format, VkExtent2D resolution, VkImageUsageFlags usage, VkImageAspectFlags aspectFlags, VkImageLayout initLayout)
{
    VkImage image;

    VkImageCreateInfo info = {};
    info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
    info.format = format;
    info.imageType = VK_IMAGE_TYPE_2D;
    info.initialLayout = initLayout;
    info.samples = config_.getAntialiasing();
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