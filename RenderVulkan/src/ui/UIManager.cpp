#include <ui/UIManager.hpp>
#include <ui/UISkContextBuilder.hpp>
#include <skia/include/gpu/GrSurfaceInfo.h>
#include <skia/include/gpu/vk/GrVkTypes.h>
#include <skia/include/core/SkSurface.h>

using namespace CubA4::render::ui;
using namespace CubA4::render::engine::memory;

UIManager::UIManager(std::shared_ptr<const CubA4::render::vulkan::Instance> instance,
    std::shared_ptr<const CubA4::render::vulkan::Device> device) :
    instance_(instance), device_(device), context_(createContext(instance, device)), allocator_(device)
{
    
}

UIManager::~UIManager() = default;

void UIManager::initFramebuffer(VkFormat format, VkExtent2D resolution)
{
    GrVkImageInfo imageInfo {

    };
    GrBackendRenderTarget renderTarget;
    // SkSurface::MakeFromBackendRenderTarget(context_->get().get(), renderTarget, kTopLeft_GrSurfaceOrigin, kRGBA_8888_SkColorType, )
}

std::shared_ptr<UISkContext> UIManager::createContext(std::shared_ptr<const CubA4::render::vulkan::Instance> instance,
    std::shared_ptr<const CubA4::render::vulkan::Device> device)
{
    UISkContextBuilder builder(instance, device);
    return builder.createContext();
}
