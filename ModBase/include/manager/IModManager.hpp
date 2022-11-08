#pragma once

#include <memory>
#include <manager/IModBlockManager.hpp>
#include <manager/IModRenderManager.hpp>
#include <manager/IModItemManager.hpp>

namespace CubA4::manager
{
	/* Интерфейс, позволяющий получить доступ к ресурсам мода */
	class IModManager
	{
	public:
		virtual std::shared_ptr<const IModBlockManager> getBlockManager() const = 0;
	protected:
		explicit IModManager() = default;
		virtual ~IModManager() = default;
	private:
	};
}
