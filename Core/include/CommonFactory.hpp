#pragma once

#include <memory>
#include <ICore.hpp>
#include <CoreExportHelper.hpp>
#include <system/IStartup.hpp>

namespace CubA4
{
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
