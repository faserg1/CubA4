#include "./RenderPassBuilder.hpp"
#include "./RenderPass.hpp"
#include "./Device.hpp"
#include "./Swapchain.hpp"
#include <vector>
using namespace CubA4::render::vulkan;

RenderPassBuilder::RenderPassBuilder(std::shared_ptr<const Device> device, std::shared_ptr<const Swapchain> swapchain, CubA4::render::config::VulkanConfigAdapter config) :
	device_(device), swapchain_(swapchain), config_(config)
{

}

RenderPassBuilder::~RenderPassBuilder()
{
	
}

std::shared_ptr<RenderPass> RenderPassBuilder::build()
{
	VkRenderPassCreateInfo renderPassCreateInfo = {};
	renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;

	//Рассчитывать будем на то, что у нас сейчас только один выход - цвет, и ничего нет на вход.
	//После здесь добавятся буфер глубины и т.д. и т.п
	//Не забыть про всю эту фигню при создании фреймбуфера и очистке (в начале прохода рендеринга)

	VkAttachmentDescription colorAttachment = {};
	colorAttachment.format = swapchain_->getFormat();
	// TODO: [OOKAMI] Multisampling settings
	colorAttachment.samples = config_.getAntialiasing();
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkAttachmentDescription depthAttachment = {};
	depthAttachment.format = VK_FORMAT_D32_SFLOAT_S8_UINT;
	// TODO: [OOKAMI] Multisampling settings
	depthAttachment.samples = config_.getAntialiasing();
	depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	VkAttachmentDescription resolveAttachment = {};
	resolveAttachment.format = swapchain_->getFormat();
	resolveAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	resolveAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	resolveAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	resolveAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	resolveAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	resolveAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	resolveAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	std::vector<VkAttachmentDescription> attachments =
	{
		colorAttachment,
		depthAttachment,
		resolveAttachment
	};

	renderPassCreateInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
	renderPassCreateInfo.pAttachments = attachments.data();

	//////////////////////////////////////////////

	VkAttachmentReference colorAttachmentReference = {};
	colorAttachmentReference.attachment = 0;
	colorAttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkAttachmentReference depthAttachmentReference = {};
	depthAttachmentReference.attachment = 1;
	depthAttachmentReference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	VkAttachmentReference resolveAttachmentReference = {};
	resolveAttachmentReference.attachment = 2;
	resolveAttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	//И так, по началу будем расчитывать на то, что существует один проход рендеринга с одним подпроходом.
	//В дальнейшем подпроходов может быть больше, к примеру:
	//Отрисовка атмосферы (кубмап), отрисовка основных объектов, отрисовка скелетонов, где то тут прозрачные объекты, пост обработка

	VkSubpassDescription mainSubpass = {};
	mainSubpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	mainSubpass.colorAttachmentCount = 1;
	mainSubpass.pColorAttachments = &colorAttachmentReference;
	mainSubpass.pDepthStencilAttachment = &depthAttachmentReference;
	mainSubpass.pResolveAttachments = &resolveAttachmentReference;

	/*VkSubpassDescription uiSubpass = {};
	uiSubpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	uiSubpass.colorAttachmentCount = 1;
	uiSubpass.pColorAttachments = &resolveAttachmentReference;
	uiSubpass.pDepthStencilAttachment = &depthAttachmentReference;*/

	std::vector<VkSubpassDescription> subpasses =
	{
		mainSubpass,
		//uiSubpass
	};

	renderPassCreateInfo.subpassCount = static_cast<uint32_t>(subpasses.size());
	renderPassCreateInfo.pSubpasses = subpasses.data();

	//////////////////////////////////////////////

	VkSubpassDependency uiDep
	{
		.srcSubpass = 0,
		.dstSubpass = 1,
		.srcStageMask = VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT,
		.dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
		.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
		.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT,
	};
	std::vector<VkSubpassDependency> deps
	{
		//uiDep
	};
	

	renderPassCreateInfo.dependencyCount = static_cast<uint32_t>(deps.size());
	renderPassCreateInfo.pDependencies = deps.data();

	VkRenderPass renderPass;
	if (vkCreateRenderPass(device_->getDevice(), &renderPassCreateInfo, nullptr, &renderPass) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exception, etc
		return {};
	}
	device_->getMarker().setName(renderPass, "Default Render Pass");
	return std::make_shared<RenderPass>(device_, renderPass);
}