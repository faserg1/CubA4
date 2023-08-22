#pragma once

#include <memory>
#include <manager/IModManager.hpp>
#include <manager/ModBlockManager.hpp>
#include <manager/ModEntityManager.hpp>
#include <manager/ModRenderManager.hpp>

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

		std::shared_ptr<const IModEntityManager> getEntityManager() const override;
		std::shared_ptr<ModEntityManager> getEntityManager();

		std::shared_ptr<const IModRenderManager> getRenderManager() const override;
		std::shared_ptr<ModRenderManager> getRenderManager();
	protected:
	private:
		std::shared_ptr<ModBlockManager> blockManager_;
		std::shared_ptr<ModEntityManager> entityManager_;
		std::shared_ptr<ModRenderManager> renderManager_;
	};
}
