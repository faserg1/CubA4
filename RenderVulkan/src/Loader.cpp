#include "VulkanInfo.hpp"
#include "RenderExportHelper.hpp"

extern "C"
{
	RENDER_LIBRARY_EXPORT CubA4::render::IRenderInfo *getRenderInfo()
	{
		return new CubA4::render::VulkanInfo();
	}
}