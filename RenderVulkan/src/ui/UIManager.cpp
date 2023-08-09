#include <ui/UIManager.hpp>
#include <ui/UISkContextBuilder.hpp>
#include <ui/utils/ColorUtils.hpp>
#include <skia/include/gpu/GrSurfaceInfo.h>
#include <skia/include/gpu/vk/GrVkTypes.h>
#include <skia/include/core/SkSurface.h>
#include <skia/include/core/SkColorSpace.h>

using namespace CubA4::render::ui;

UIManager::UIManager(std::shared_ptr<const CubA4::render::vulkan::Instance> instance,
    std::shared_ptr<const CubA4::render::vulkan::Device> device) :
    instance_(instance), device_(device), context_(createContext(instance, device))
{
    componentFactory_ = std::make_shared<ComponentFactory>(context_);
    mainCanvas_ = std::make_shared<MainCanvas>();
}

UIManager::~UIManager()
{
	context_->get()->abandonContext();
}

std::shared_ptr<IComponentFactory> UIManager::getComponentFactory() const
{
	return componentFactory_;
}

std::shared_ptr<IMainCanvas> UIManager::getMainCanvas() const
{
	return mainCanvas_;
}

void UIManager::swapchainChanged(std::shared_ptr<const CubA4::render::vulkan::Swapchain> swapchain)
{
	framebuffers_.clear(); // TODO: [OOKAMI] Make old as in framebuffer manager?
	auto images = swapchain->getImages();
	auto [width, height] = swapchain->getResolution();
	for (auto &image : images)
	{
		GrVkImageInfo imageInfo {
			.fImage = image,
			.fImageLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
			.fFormat = swapchain->getFormat(),
			.fImageUsageFlags = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT,
			.fLevelCount = 1
    	};
		GrBackendRenderTarget renderTarget(width, height, imageInfo);
		GrSurfaceOrigin origin = kTopLeft_GrSurfaceOrigin;
		SkColorType colorType = getColorType(swapchain->getFormat());
		auto colorSpace = SkColorSpace::MakeSRGB();
		auto surface = SkSurface::MakeFromBackendRenderTarget(context_->get().get(), renderTarget, origin, colorType, colorSpace, nullptr);

		UIFramebuffer framebuffer {
			.surface = surface,
			.renderDoneSemaphore = CubA4::render::vulkan::Semaphore::create(device_)
		};

		framebuffers_.push_back(framebuffer);
	}

	Context ctx {
		.viewportWidth = static_cast<long double>(width),
		.viewportHeight = static_cast<long double>(height),
		.parentWidth = static_cast<long double>(width),
		.parentHeight = static_cast<long double>(height)
	};

	mainCanvas_->updateContext(ctx);
}

const UIFramebuffer &UIManager::getFramebuffer(uint32_t imageIdx) const
{
	return framebuffers_[imageIdx];
}

void UIManager::drawOn(uint32_t imageIdx)
{
	auto &surface = framebuffers_[imageIdx].surface;
	auto canvas = surface->getCanvas();
	mainCanvas_->draw(canvas);
}

void UIManager::submit()
{
	context_->get()->submit();
}

std::shared_ptr<UISkContext> UIManager::createContext(std::shared_ptr<const CubA4::render::vulkan::Instance> instance,
    std::shared_ptr<const CubA4::render::vulkan::Device> device)
{
    UISkContextBuilder builder(instance, device);
    return builder.createContext();
}
