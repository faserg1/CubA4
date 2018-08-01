#ifndef MODVANILLA_HPP
#define MODVANILLA_HPP

#include <mod/IMod.hpp>

namespace CubA4
{
	namespace mod
	{
		class ModVanilla :
			public virtual IMod
		{
		public:
			explicit ModVanilla();
			~ModVanilla();

			void load(std::shared_ptr<const core::ICore> core) override;
			void preinit() override;
			void link(std::shared_ptr<const IModLinker> linker) override;
			void init(std::shared_ptr<CubA4::core::system::IEnvironmentBuilder> builder) override;
			void configure() override;
			void done() override;

			void preunload() override;
		protected:
		private:
			std::shared_ptr<const core::ICore> core_;
		};
	}
}

#endif // MODVANILLA_HPP
