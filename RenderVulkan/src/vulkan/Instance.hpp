#ifndef INSTANCE_HPP 
#define INSTANCE_HPP 

#include <vulkan/vulkan.h>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Instance 
			{
			public:
				explicit Instance(VkInstance instance);
				~Instance();
				VkInstance getInstance() const;
			protected:
				
			private:
				const VkInstance instance_;
			};
		}
	}
}

#endif // INSTANCE_HPP 
