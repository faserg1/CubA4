#pragma once

#include <memory>
#include <system/IAppCallback.hpp>
#include <game/IGame.hpp>

namespace CubA4::system
{
	class IStartup
	{
	public:
		virtual void load(IAppCallback &appCallback) = 0;

		virtual void setup() = 0;
		virtual void shutdown() = 0;

		virtual void run() = 0;
		virtual void stop() = 0;

		virtual std::shared_ptr<CubA4::game::IGame> getGame() const = 0;
	protected:
		explicit IStartup() = default;
		virtual ~IStartup() = default;
	private:
	};
}
