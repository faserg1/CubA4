#include "VulkanInfo.hpp"
#include "ExportHelper.hpp"

extern "C"
{
	LIBRARY_EXPORT CubA4::render::RenderInfo *getRenderInfo()
	{
		return new CubA4::render::VulkanInfo();
	}
}