#include <engine/RenderUI.hpp>
using namespace CubA4::render::engine;

RenderUI::RenderUI(std::shared_ptr<const vulkan::Device> device) :
    device_(device)
{

}

void RenderUI::recordApplyUI(VkCommandBuffer cmd)
{

}