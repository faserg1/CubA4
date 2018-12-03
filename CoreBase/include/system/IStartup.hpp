#ifndef ISTARTUP_HPP
#define ISTARTUP_HPP

#include <memory>

namespace CubA4
{
	namespace mod
	{
		class IModLoader;
	}

	namespace core
	{
		namespace game
		{
			class IGame;
		}

		namespace system
		{
			class IAppCallback;

			class IStartup
			{
			public:
				virtual void load(IAppCallback &appCallback) = 0;
				virtual void unload() = 0;

				virtual void setup() = 0;
				virtual void shutdown() = 0;

				virtual void run() = 0;
				virtual void stop() = 0;

				virtual std::shared_ptr<CubA4::core::game::IGame> getGame() const = 0;
			protected:
				explicit IStartup() = default;
				virtual ~IStartup() = default;
			private:
			};
		}
	}
}

#endif // ISTARTUP_HPP
