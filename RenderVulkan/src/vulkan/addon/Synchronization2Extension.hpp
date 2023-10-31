#pragma once

#include <vulkan/addon/DeviceExtension.hpp>

namespace CubA4::render::vulkan::addon
{
	class Synchronization2Extension :
		public DeviceExtension
	{
	public:
		explicit Synchronization2Extension(std::weak_ptr<PhysicalDevice> physicalDevice);
		~Synchronization2Extension();

		std::vector<std::string> names() const override;
		void init(std::shared_ptr<const Device> instance) override;
		void destroy(std::shared_ptr<const Device> instance) override;
		void added(DeviceBuilder &builder) override;
	protected:
	private:
	};
}
