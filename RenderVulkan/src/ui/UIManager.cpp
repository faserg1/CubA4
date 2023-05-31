#include <ui/UIManager.hpp>
#include <ui/UISkContextBuilder.hpp>
#include <skia/include/gpu/GrSurfaceInfo.h>
#include <skia/include/gpu/vk/GrVkTypes.h>
#include <skia/include/core/SkSurface.h>
#include <skia/include/core/SkCanvas.h>
#include <skia/include/core/SkFont.h>
#include <skia/include/core/SkColorSpace.h>

using namespace CubA4::render::ui;

UIManager::UIManager(std::shared_ptr<const CubA4::render::vulkan::Instance> instance,
    std::shared_ptr<const CubA4::render::vulkan::Device> device) :
    instance_(instance), device_(device), context_(createContext(instance, device))
{
    
}

UIManager::~UIManager() = default;

void UIManager::swapchainChanged(std::shared_ptr<const CubA4::render::vulkan::Swapchain> swapchain)
{
	framebuffers_.clear(); // TODO: [OOKAMI] Make as in framebuffer manager?
	auto images = swapchain->getImages();
	for (auto &image : images)
	{
		auto [width, height] = swapchain->getResolution();
		GrVkImageInfo imageInfo {
			.fImage = image,
			.fImageLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
			.fFormat = swapchain->getFormat(),
			.fImageUsageFlags = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT,
			.fLevelCount = 1
    	};
		GrBackendRenderTarget renderTarget(width, height, imageInfo);
		GrSurfaceOrigin origin = kTopLeft_GrSurfaceOrigin;
		SkColorType colorType = kBGRA_8888_SkColorType;
		auto colorSpace = SkColorSpace::MakeSRGB();
		auto surface = SkSurface::MakeFromBackendRenderTarget(context_->get().get(), renderTarget, origin, colorType, colorSpace, nullptr);

		UIFramebuffer framebuffer {
			.surface = surface,
			.renderDoneSemaphore = CubA4::render::vulkan::Semaphore::create(device_)
		};

		framebuffers_.push_back(framebuffer);
	}
}

const UIFramebuffer &UIManager::getFramebuffer(uint32_t imageIdx) const
{
	return framebuffers_[imageIdx];
}

void UIManager::drawOn(uint32_t imageIdx)
{
	// test!!!
	auto &surface = framebuffers_[imageIdx].surface;
	auto canvas = surface->getCanvas();
	SkPoint center = {200, 200};
	SkScalar rad = 100;
	
	SkColor4f color = {0, 0, 0, 1};
	SkPaint paint(color);
	canvas->drawCircle(center, rad, paint);

	std::string text("UI is here!");
	SkFont font;
	font.setSize(32);
	canvas->drawSimpleText(text.data(), text.size(), SkTextEncoding::kUTF8, 100, 400, font, paint);
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
