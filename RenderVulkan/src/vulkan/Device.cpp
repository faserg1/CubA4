#include "./Device.hpp"
#include <functional>
using namespace CubA4::render::vulkan;

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Queue :
				public virtual IQueue
			{
			public:
				Queue(VkQueue queue, std::function<void()> deleter) :
					queue_(queue), deleter_(deleter)
				{

				}
				~Queue()
				{
					deleter_();
				}
				VkQueue get() const override
				{
					return queue_;
				}
			private:
				const VkQueue queue_;
				std::function<void()> deleter_;
			};
		}
	}
}

Device::Device(VkDevice device, VkPhysicalDevice physicalDevice, VkQueue queue) :
	device_(device), physicalDevice_(physicalDevice), queue_(queue), queueLock_(false), marker_(*this)
{
	marker_.setName(device_, "Default logical device");
}

Device::~Device()
{
	
}

VkDevice Device::getDevice() const
{
	return device_;
}

VkPhysicalDevice Device::getPhysicalDevice() const
{
	return physicalDevice_;
}

std::unique_ptr<IQueue> Device::getQueue() const
{
	std::function<void()> deleter = [&lock = queueLock_]()
	{
		lock = false;
	};
	while (queueLock_);
	queueLock_ = true;
	return std::make_unique<Queue>(queue_, deleter);
}

DebugMarker &Device::getMarker() const
{
	return marker_;
}