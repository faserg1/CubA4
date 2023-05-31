#include <engine/RenderUI.hpp>
#include <skia/include/core/SkSurface.h>
#include <skia/include/gpu/GrBackendSemaphore.h>
using namespace CubA4::render::engine;

RenderUI::RenderUI(std::shared_ptr<const vulkan::Device> device,
	std::shared_ptr<FramebufferManager> framebufferManager,
	std::shared_ptr<RenderManager> renderManager) :
    device_(device), framebufferManager_(framebufferManager), renderManager_(renderManager)
{

}

std::shared_ptr<CubA4::render::vulkan::Semaphore> RenderUI::render(uint32_t imgIndex, std::shared_ptr<const vulkan::Semaphore> awaitSemaphore)
{
	auto uiManager = renderManager_->getUIManager();
	auto &framebuffer = uiManager->getFramebuffer(imgIndex);
	GrBackendSemaphore backendAwaitSemaphore;
	backendAwaitSemaphore.initVulkan(awaitSemaphore->getSemaphore());

	GrBackendSemaphore backendDoneSemaphore;
	backendDoneSemaphore.initVulkan(framebuffer.renderDoneSemaphore->getSemaphore());

	auto surface = framebuffer.surface;

	surface->wait(1, &backendAwaitSemaphore, false);
	uiManager->drawOn(imgIndex);

	GrFlushInfo flushInfo {
		.fNumSemaphores = 1,
		.fSignalSemaphores = &backendDoneSemaphore
	};

	if (surface->flush(SkSurface::BackendSurfaceAccess::kPresent, flushInfo) == GrSemaphoresSubmitted::kYes)
	{
		uiManager->submit();
		return framebuffer.renderDoneSemaphore;
	}
	
	return {};
}