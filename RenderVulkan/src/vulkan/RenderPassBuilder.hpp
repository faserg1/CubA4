#ifndef RENDERPASSBUILDER_HPP
#define RENDERPASSBUILDER_HPP

#include <memory>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Device;
			class RenderPass;
			class Swapchain;

			class RenderPassBuilder
			{
			public:
				explicit RenderPassBuilder(std::shared_ptr<const Device> device, std::shared_ptr<const Swapchain> swapchain);
				~RenderPassBuilder();

				std::shared_ptr<RenderPass> build();
			protected:
			private:
				const std::shared_ptr<const Device> device_;
				const std::shared_ptr<const Swapchain> swapchain_;
			};
		}
	}
}

#endif // RENDERPASSBUILDER_HPP
