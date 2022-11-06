#pragma once

#include <memory>
#include <game/IGame.hpp>
#include <window/IWindow.hpp>
#include <engine/IRenderManager.hpp>

namespace CubA4::render::engine
{
	class IRenderEngine
	{
	public:
		virtual ~IRenderEngine() = default;

		virtual void init(std::shared_ptr<const window::IWindow> window) = 0;
		virtual void destroy() = 0;

		virtual void setGame(std::shared_ptr<const CubA4::game::IGame> game) = 0;

		virtual void run() = 0;
		virtual void stop() = 0;

		virtual std::shared_ptr<IRenderManager> getRenderManager() const = 0;
	protected:
		explicit IRenderEngine() = default;
	private:
	};
}
