#ifndef MEMORYMANAGER_HPP
#define MEMORYMANAGER_HPP

#include <map>
#include <memory>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Memory;
		}

		namespace engine
		{
			// TODO: [OOKAMI] Класс будет хранить и распределять участки памяти определённого типа

			class MemoryManager
			{
			public:
				explicit MemoryManager();
				~MemoryManager();


			protected:
			private:

			};
		}
	}
}

#endif // MEMORYMANAGER_HPP
