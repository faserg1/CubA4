#pragma once

#include <memory>
#include <manager/IModManager.hpp>
#include <manager/ModBlockManager.hpp>

namespace CubA4::manager
{
	class ModManager :
		public virtual IModManager
	{
	public:
		explicit ModManager();
		~ModManager();

		std::shared_ptr<const IModBlockManager> getBlockManager() const override;
		std::shared_ptr<ModBlockManager> getBlockManager();
	protected:
	private:
		std::shared_ptr<ModBlockManager> blockManager_;
	};
}

