#pragma once

#include <memory>
#include <functional>
#include <game/controller/Buttons.hpp>
#include <system/IAppCallback.hpp>

namespace CubA4::render
{
	class IRenderInfo;

	namespace engine
	{
		class IRenderManager;
	}
}

namespace CubA4::system
{
	class IAppClientCallback : public virtual IAppCallback
	{
	public:
		virtual std::shared_ptr<render::engine::IRenderManager> getRenderManager() const = 0;
		virtual const render::IRenderInfo &getRenderInfo() const = 0;
		virtual std::pair<bool, CubA4::game::controller::BMods> getButtonState(CubA4::game::controller::Button btn) const = 0;
		virtual bool requestMouseCapture(bool enable) = 0;
	protected:
		virtual ~IAppClientCallback() = default;
		explicit IAppClientCallback() = default;
	private:
	};
}
