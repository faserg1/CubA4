#include "./Texture.hpp"
#include "../../vulkan/Device.hpp"
using namespace CubA4::render::engine::material;
using namespace CubA4::render::engine::memory;
using namespace CubA4::render::vulkan;

Texture::Texture(std::shared_ptr<const Device> device, VkImage texture, VkImageView textureView, std::shared_ptr<const IMemoryPart> part) :
	device_(device), texture_(texture), textureView_(textureView), memoryPart_(part)
{
	
}

Texture::~Texture()
{
	vkDestroyImageView(device_->getDevice(), textureView_, nullptr);
	vkDestroyImage(device_->getDevice(), texture_, nullptr);
}

VkImage Texture::getTexture() const
{
	return texture_;
}

VkImageView Texture::getTextureView() const
{
	return textureView_;
}