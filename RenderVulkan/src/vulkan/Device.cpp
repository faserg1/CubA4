#include "./Device.hpp"
#include <functional>
using namespace CubA4::render::vulkan;

namespace CubA4::render::vulkan
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

Device::Device(VkDevice device, VkPhysicalDevice physicalDevice, VkQueue renderQueue, VkQueue transmitQueue,
	std::vector<std::string> extensions, VkPhysicalDeviceFeatures2 enabledFeatures) :
	device_(device), physicalDevice_(physicalDevice), marker_(*this), extensions_(extensions), enabledFeatures_(enabledFeatures)
{
	renderQueue_.queue = renderQueue;
	transmitQueue_.queue = transmitQueue;
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

std::unique_ptr<IQueue> Device::getQueue(QueueType type) const
{
	const Device::QueueData *data = nullptr;
	bool needLock = true;
	switch (type)
	{
	case CubA4::render::vulkan::QueueType::Render:
		data = &renderQueue_;
		break;
	case CubA4::render::vulkan::QueueType::Transmit:
		data = &transmitQueue_;
		break;
	default:
		return {};
	}
	std::function<void()> deleter = [data, needLock]()
	{
		if (needLock)
			data->mutex.unlock();
	};
	if (needLock)
		data->mutex.lock();
	return std::make_unique<Queue>(data->queue, deleter);
}

const std::vector<std::string> &Device::getEnabledExtensions() const
{
	return extensions_;
}

const VkPhysicalDeviceFeatures2 &Device::getEnabledFeatures() const
{
	return enabledFeatures_;
}

DebugMarker &Device::getMarker() const
{
	return marker_;
}