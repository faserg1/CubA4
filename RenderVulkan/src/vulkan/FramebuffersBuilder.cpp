#include <vulkan/FramebuffersBuilder.hpp>
using namespace CubA4::render::vulkan;

FramebuffersBuilder::FramebuffersBuilder(std::shared_ptr<const vulkan::Device> device) :
    device_(device), allocator_(device), commandPool_(device, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT)
{
	
}

FramebuffersBuilder::~FramebuffersBuilder()
{
	
}

std::vector<std::shared_ptr<Framebuffer>> FramebuffersBuilder::createFramebuffers(std::shared_ptr<const Swapchain> swapchain, std::shared_ptr<const vulkan::RenderPass> renderPass)
{
    uint32_t imgCount = swapchain->getImageCount();
	std::vector<VkImage> images(imgCount);
    std::vector<VkCommandBuffer> cmdBuffers(imgCount);
    std::vector<std::shared_ptr<Framebuffer>> framebuffers(imgCount);

    //get swapchain images
	auto vkSwapchain = swapchain->getSwapchain();
	vkGetSwapchainImagesKHR(device_->getDevice(), vkSwapchain, &imgCount, images.data());

    commandPool_.allocate(imgCount, cmdBuffers.data());
    auto [width, height] = swapchain->getResolution();
    auto format = swapchain->getFormat();
    auto vkRenderPass = renderPass->getRenderPass();
    for (size_t idx = 0; idx < imgCount; idx++)
    {
        
        framebuffers[idx] = std::make_shared<Framebuffer>(
            device_, allocator_, images[idx], format, width, height,
            vkRenderPass, cmdBuffers[idx]);
    }
    
	
    return std::move(framebuffers);
}