#pragma once

#pragma once

#include <memory>
#include <vulkan/Framebuffer.hpp>
#include <vulkan/Semaphore.hpp>

namespace CubA4::render::engine::pipeline
{
	class IMainEnginePipelineItem
	{
	public:
		// TODO: separate into 2 methods - record and submit
		virtual std::shared_ptr<const vulkan::Semaphore> render(uint32_t frame,
			std::shared_ptr<const vulkan::Semaphore> awaitSemaphore) = 0;
	protected:
		IMainEnginePipelineItem() = default;
		~IMainEnginePipelineItem() = default;
	};
}