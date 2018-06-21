#ifndef SURFACE_HPP 
#define SURFACE_HPP 

#include <vulkan/vulkan.h>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Surface 
			{
			public:
				explicit Surface(VkSurfaceKHR surafece);
				~Surface();

				VkSurfaceKHR getSurface() const;
			protected:
			private:
				const VkSurfaceKHR surface_;
			};
		}
	}
}

#endif // SURFACE_HPP 
