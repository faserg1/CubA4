#pragma once

#include <memory>
#include <IModVanilla.hpp>
#include <startup/RenderStartup.hpp>
#include <startup/BlockSetup.hpp>
#include <startup/WorldSetup.hpp>
#include <manager/IModManager.hpp>

namespace CubA4
{
	namespace mod
	{
		class ModVanilla :
			public virtual IModVanilla
		{
		public:
			explicit ModVanilla(const IModInfo &modInfo);
			~ModVanilla();

			void load(std::shared_ptr<const ICore> core) override;
			void preinit(std::shared_ptr<CubA4::system::IEnvironmentBuilder> builder) override;
			void link(std::shared_ptr<const IModLinker> linker) override;
			void init(std::shared_ptr<CubA4::system::IEnvironmentBuilder> builder) override;
			void configure(std::shared_ptr<CubA4::system::IEnvironmentBuilder> builder) override;
			void prefinish(std::shared_ptr<CubA4::system::IEnvironmentBuilder> builder) override;
			void finish() override;

			void preunload() override;

			const IModInfo &getInfo() const override;
			std::weak_ptr<const CubA4::manager::IModManager> getManager() const override;
		protected:
		private:
			const IModInfo &modInfo_;
			std::shared_ptr<const ICore> core_;
			startup::RenderStartup renderStartup_;
			startup::BlockSetup blockSetup_;
			startup::WorldSetup worldSetup_;
			std::shared_ptr<CubA4::manager::ModManager> manager_;
		};
	}
}

