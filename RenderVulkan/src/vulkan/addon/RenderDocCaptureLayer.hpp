#pragma once

#include <vulkan/addon/InstanceLayer.hpp>

namespace CubA4::render::vulkan::addon
{
	class RenderDocCaptureLayer :
		public InstanceLayer
	{
	public:
		explicit RenderDocCaptureLayer();
		~RenderDocCaptureLayer();

		std::vector<std::string> names() const override;
		void init(std::shared_ptr<const Instance> instance) override;
		void destroy(std::shared_ptr<const Instance> instance) override;
		void added(InstanceBuilder &builder) override;
	protected:
	private:
	};
}
