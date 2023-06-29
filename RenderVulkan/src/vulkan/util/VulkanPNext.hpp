#pragma once

#include <memory>
#include <vector>

namespace CubA4::render::vulkan::util
{
	class VulkanPNextContainer
	{
	public:
	protected:
		template <class TypeNext, class VulkanType>
		void *addPNext(TypeNext next, VulkanType *to)
		{
			auto pNext = std::make_shared<TypeNext>(next);
			struct NoneType
			{
				VkStructureType type;
				void *pNext;
			};
			NoneType *current = reinterpret_cast<NoneType*>(to);
			while (current->pNext)
				current = reinterpret_cast<NoneType*>(current->pNext);
			current->pNext = pNext.get();
			auto voidpNext = std::reinterpret_pointer_cast<void>(pNext);
			pNexts_.push_back(voidpNext);
			return pNext.get();
		}
	private:
		std::vector<std::shared_ptr<void>> pNexts_;
	};
}