#ifndef IMODMANAGER_HPP
#define IMODMANAGER_HPP

#include <memory>

namespace CubA4
{
	namespace mod
	{
		namespace manager
		{
			class IModRenderManager;
			class IModBlockManager;
			class IModItemManager;

			/* Интерфейс, позволяющий получить доступ к ресурсам мода */
			class IModManager
			{
			public:
				virtual std::weak_ptr<const IModRenderManager> getModRenderManager() const = 0;
			protected:
				explicit IModManager() = default;
				virtual ~IModManager() = default;
			private:
			};
		}
	}
}

#endif // IMODMANAGER_HPP
