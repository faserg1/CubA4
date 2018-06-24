#ifndef SEMAPHORE_HPP
#define SEMAPHORE_HPP

#include <memory>
#include <vulkan/vulkan.h>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Device;

			class Semaphore final
			{
			public:
				explicit Semaphore(VkSemaphore semaphore, std::weak_ptr<const Device> device);
				static std::shared_ptr<Semaphore> create(std::shared_ptr<const Device> device);
				~Semaphore();

				VkSemaphore getSemaphore() const;
			protected:
			private:
				std::weak_ptr<const Device> device_;
				VkSemaphore semaphore_;
			};
		}
	}
}

#endif // SEMAPHORE_HPP
