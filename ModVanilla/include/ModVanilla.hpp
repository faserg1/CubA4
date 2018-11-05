#ifndef MODVANILLA_HPP
#define MODVANILLA_HPP

#include <mod/IMod.hpp>
#include "startup/RenderStartup.hpp"
#include "startup/WorldSetup.hpp"
#include "manager/ModManager.hpp"

namespace CubA4
{
	namespace mod
	{
		class ModVanilla :
			public virtual IMod
		{
		public:
			explicit ModVanilla(const IModInfo &modInfo);
			~ModVanilla();

			void load(std::shared_ptr<const core::ICore> core) override;
			void preinit(std::shared_ptr<CubA4::core::system::IEnvironmentBuilder> builder) override;
			void link(std::shared_ptr<const IModLinker> linker) override;
			void init(std::shared_ptr<CubA4::core::system::IEnvironmentBuilder> builder) override;
			void configure(std::shared_ptr<CubA4::core::system::IEnvironmentBuilder> builder) override;
			void done(std::shared_ptr<CubA4::core::system::IEnvironmentBuilder> builder) override;

			void preunload() override;

			const IModInfo &getInfo() const override;
			std::weak_ptr<const manager::IModManager> getManager() const override;
		protected:
		private:
			const IModInfo &modInfo_;
			std::shared_ptr<const core::ICore> core_;
			startup::RenderStartup renderStartup_;
			startup::WorldSetup worldSetup_;
			std::shared_ptr<manager::ModManager> manager_;
		};
	}
}

#endif // MODVANILLA_HPP
