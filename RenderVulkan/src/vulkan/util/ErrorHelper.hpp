#ifndef ERRORHELPER_HPP
#define ERRORHELPER_HPP

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
					
					static std::string getResultString(VkResult result) const;
				protected:
				private:
					
				};
			}
		}
	}
}

#endif // ERRORHELPER_HPP
