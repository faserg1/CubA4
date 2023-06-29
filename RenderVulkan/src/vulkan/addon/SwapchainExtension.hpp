#pragma once

#include <vulkan/addon/DeviceExtension.hpp>

namespace CubA4::render::vulkan::addon
{
	class SwapchainExtension :
		public DeviceExtension
	{
	public:
		explicit SwapchainExtension(std::weak_ptr<PhysicalDevice> physicalDevice);
		~SwapchainExtension();

		std::vector<std::string> names() const override;
		void init(std::shared_ptr<const Device> instance) override;
		void destroy(std::shared_ptr<const Device> instance) override;
		void added(DeviceBuilder &builder) override;
	protected:
	private:
	};
}
