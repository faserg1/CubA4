#include "./RenderPassBuilder.hpp"
#include "./RenderPass.hpp"
#include "./Device.hpp"
#include "./Swapchain.hpp"
#include <vector>
using namespace CubA4::render::vulkan;

RenderPassBuilder::RenderPassBuilder(std::shared_ptr<const Device> device, std::shared_ptr<const Swapchain> swapchain) :
	device_(device), swapchain_(swapchain)
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
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	std::vector<VkAttachmentDescription> attachments =
	{
		colorAttachment
	};

	renderPassCreateInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
	renderPassCreateInfo.pAttachments = attachments.data();

	VkAttachmentReference colorAttachmentReference = {};
	colorAttachmentReference.attachment = 0;
	colorAttachmentReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	//И так, по началу будем расчитывать на то, что существует один проход рендеринга с одним подпроходом.
	//В дальнейшем подпроходов может быть больше, к примеру:
	//Отрисовка атмосферы (кубмап), отрисовка основных объектов, отрисовка скелетонов, где то тут прозрачные объекты, пост обработка

	VkSubpassDescription mainSubpass = {};
	mainSubpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	mainSubpass.colorAttachmentCount = 1;
	mainSubpass.pColorAttachments = &colorAttachmentReference;

	std::vector<VkSubpassDescription> subpasses =
	{
		mainSubpass
	};

	renderPassCreateInfo.subpassCount = static_cast<uint32_t>(subpasses.size());
	renderPassCreateInfo.pSubpasses = subpasses.data();

	VkRenderPass renderPass;
	if (vkCreateRenderPass(device_->getDevice(), &renderPassCreateInfo, nullptr, &renderPass) != VK_SUCCESS)
	{
		// TODO: [OOKAMI] Exception, etc
		return {};
	}
	device_->getMarker().setName(renderPass, "Default Render Pass");
	return std::make_shared<RenderPass>(device_, renderPass);
}