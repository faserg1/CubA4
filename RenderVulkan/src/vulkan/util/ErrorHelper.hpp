#pragma once

#include <vulkan/vulkan.h>
#include <string>

namespace CubA4::render::vulkan::util
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
