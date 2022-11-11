#pragma once

#include <engine/material/DescriptorPool.hpp>

namespace CubA4::render::engine::material
{
	class TexturesDescriptorPool : public DescriptorPool
	{
	public:
		explicit TexturesDescriptorPool(std::shared_ptr<const vulkan::Device> device);
		~TexturesDescriptorPool();
	protected:
		uint32_t getMaxSetCount() const override;
		std::vector<VkDescriptorPoolSize> getPoolSizes() const override;
	};
}
