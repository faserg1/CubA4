#ifndef RENDERVULKAN_DEBUGMARKER_HPP
#define RENDERVULKAN_DEBUGMARKER_HPP

#include <memory>
#include <vulkan/vulkan.h>
#include <typeinfo>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Device;

			class DebugMarker
			{
				friend class Device;
			public:
				template <class TVkObjectType>
				bool setName(TVkObjectType vkObject, const char *name)
				{
					if (!setName_)
						return false;
					auto objectType = getObjectType(typeid(TVkObjectType));
					if (objectType == VK_OBJECT_TYPE_UNKNOWN)
						return false;
					setName(reinterpret_cast<uint64_t>(vkObject), objectType, name);
					return true;
				}
			protected:
				explicit DebugMarker(const Device &device);
				~DebugMarker();
			private:
				const Device &device_;
				PFN_vkSetDebugUtilsObjectNameEXT setName_;
				PFN_vkSetDebugUtilsObjectTagEXT setTag_;
			private:
				VkObjectType getObjectType(const std::type_info &typeInfo);
				void setName(uint64_t object, VkObjectType objectType, const char *name);
			};
		}
	}
}

#endif // RENDERVULKAN_DEBUGMARKER_HPP
