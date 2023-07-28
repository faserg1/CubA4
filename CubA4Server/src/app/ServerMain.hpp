#pragma once

#include <functional>
#include <memory>
#include <system/IAppCallback.hpp>

namespace CubA4::app
{
	class ServerStartup;

	class ServerMain final :
		public virtual CubA4::system::IAppCallback
	{
	public:
		explicit ServerMain(int argc, const char *const argv[]);
		~ServerMain();

		int exec();

		std::function<std::shared_ptr<mod::IModLoader>()> getModLoaderFactory() const override;
		std::shared_ptr<const CubA4::info::IApplicationInfo> getApplicationInfo() const override;
	private:
		bool setup();
		void shutdown();

		void loop(ServerStartup &startup);
	private:
		bool running_;
		std::shared_ptr<CubA4::ICore> core_;
		std::shared_ptr<CubA4::info::IApplicationInfo> info_;

		std::shared_ptr<CubA4::logging::ILoggerTagged> log_;
	};
}
