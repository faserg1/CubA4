#pragma once

#include <memory>
#include <ICore.hpp>
#include <CoreExportHelper.hpp>
#include <core/IStartup.hpp>

namespace CubA4
{
	class CORE_LIBRARY_EXPORT CommonFactory final
	{
	public:
		static std::shared_ptr<ICore> createCore(int argc, const char *const argv[], ApplicationFlags flags);
		static std::shared_ptr<core::IStartup> createStartup(std::weak_ptr<ICore> core);
	protected:
	private:
		CommonFactory() = delete;
		~CommonFactory() = delete;
	};
}
