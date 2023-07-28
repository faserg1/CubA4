#pragma once

#include <memory>
#include <system/IAppCallback.hpp>
#include <system/IStartup.hpp>
#include <ICore.hpp>

namespace CubA4::app
{
	class ServerStartup final
	{
	public:
		explicit ServerStartup(CubA4::system::IAppCallback &appCallback, std::weak_ptr<CubA4::ICore> core);
		~ServerStartup();
		ServerStartup(const ServerStartup&) = delete;
		ServerStartup(ServerStartup &&) = delete;

		void nextMainLoopIteration(double delta);

		std::shared_ptr<CubA4::system::IStartup> getSystemStartup();
	protected:
	private:
		bool setup();
		void shutdown();

		bool setupGame();
		void shutdownGame();

		void run();
		void stop();
	private:
		CubA4::system::IAppCallback &appCallback_;
		std::weak_ptr<CubA4::ICore> core_;
		std::shared_ptr<CubA4::system::IStartup> startup_;
	};
}

