#ifndef CUBA4LOADER_APPSTARTUP_HPP
#define CUBA4LOADER_APPSTARTUP_HPP

#include <memory>

namespace CubA4
{
	namespace core
	{
		class ICore;

		namespace system
		{
			class IAppCallback;
			class IStartup;
		}
	}

	namespace render
	{
		namespace engine
		{
			class IRenderEngine;
		}
	}

	namespace app
	{
		class AppStartup final
		{
		public:
			explicit AppStartup(CubA4::core::system::IAppCallback &appCallback, std::weak_ptr<CubA4::core::ICore> core, 
				std::weak_ptr<CubA4::render::engine::IRenderEngine> renderEngine);
			~AppStartup();
			AppStartup(const AppStartup&) = delete;
			AppStartup(AppStartup &&) = delete;

			void nextMainLoopIteration();
		protected:
		private:
			bool setup();
			void shutdown();

			bool setupGame();
			void shutdownGame();

			void run();
			void stop();

			void doSomeTestThings();
		private:
			CubA4::core::system::IAppCallback &appCallback_;
			std::weak_ptr<CubA4::core::ICore> core_;
			std::weak_ptr<CubA4::render::engine::IRenderEngine> renderEngine_;
			std::shared_ptr<CubA4::core::system::IStartup> startup_;
		};
	}
}

#endif // CUBA4LOADER_APPSTARTUP_HPP
