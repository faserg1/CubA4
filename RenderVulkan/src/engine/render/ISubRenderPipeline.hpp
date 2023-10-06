#pragma once

#include <vector>
#include <memory>
#include <string>
#include <array>
#include <vulkan/vulkan.h>

namespace CubA4::render::engine::pipeline
{
	class ISubRenderPipeline
	{
	public:
		using SubpipelineVersion = size_t;

		virtual ~ISubRenderPipeline() = default;

		virtual std::string debugName() const  = 0;
		virtual std::array<float, 4> debugColor() const = 0;
		virtual void onIterate() = 0;
		virtual void executeFrom(VkCommandBuffer primaryCmdBuffer) = 0;

		virtual uint32_t getSubpass() const = 0;

		virtual SubpipelineVersion getVersion() const = 0;
	protected:
		explicit ISubRenderPipeline() = default;
	};
}
