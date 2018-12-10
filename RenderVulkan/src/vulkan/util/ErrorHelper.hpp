#ifndef RENDERVULKAN_ERRORHELPER_HPP
#define RENDERVULKAN_ERRORHELPER_HPP

#include <vulkan/vulkan.h>
#include <string>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			namespace util
			{
				class ErrorHelper
				{
				public:
					ErrorHelper() = delete;
					~ErrorHelper() = delete;
					
					static std::string getResultString(VkResult result);
				protected:
				private:
					
				};
			}
		}
	}
}

#endif // RENDERVULKAN_ERRORHELPER_HPP
