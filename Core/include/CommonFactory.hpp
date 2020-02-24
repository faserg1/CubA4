#ifndef CORE_COMMONFACTORY_HPP
#define CORE_COMMONFACTORY_HPP

#include <memory>
#include <CoreExportHelper.hpp>

namespace CubA4
{
	namespace core
	{
		class ICore;

		namespace system
		{
			class IStartup;
		}

		class CORE_LIBRARY_EXPORT CommonFactory final
		{
		public:
			static std::shared_ptr<ICore> createCore(int argc, const char *const argv[]);
			static std::shared_ptr<system::IStartup> createStartup(std::weak_ptr<ICore> core);
		protected:
		private:
			CommonFactory() = delete;
			~CommonFactory() = delete;
		};
	}
}

#endif // CORE_COMMONFACTORY_HPP
