#pragma once

#include <memory>
#include <vulkan/vulkan.h>
#include <typeinfo>
#include <array>
#include <string>

namespace CubA4::render::vulkan
{
	class Device;

	class DebugMarker
	{
		friend class Device;
	public:
		template <class TVkObjectType>
		bool setName(TVkObjectType vkObject, const std::string &name)
		{
			return setName<TVkObjectType>(vkObject, name.c_str());
		}
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
		void cmdLabelBegin(VkCommandBuffer cmd, const std::string &name, std::array<float, 4> color);
		void cmdLabelEnd(VkCommandBuffer cmd);
		void cmdLabelInsert(VkCommandBuffer cmd, const std::string &name, std::array<float, 4> color);
	protected:
		explicit DebugMarker(const Device &device);
		~DebugMarker();
	private:
		const Device &device_;
		PFN_vkSetDebugUtilsObjectNameEXT setName_;
		PFN_vkSetDebugUtilsObjectTagEXT setTag_;
		PFN_vkCmdBeginDebugUtilsLabelEXT cmdBegin_;
		PFN_vkCmdEndDebugUtilsLabelEXT cmdEnd_;
		PFN_vkCmdInsertDebugUtilsLabelEXT cmdInsert_;
	private:
		VkObjectType getObjectType(const std::type_info &typeInfo);
		void setName(uint64_t object, VkObjectType objectType, const char *name);
		// TODO: 
		void setTag(uint64_t object, VkObjectType objectType);
	};
}
