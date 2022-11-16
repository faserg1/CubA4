#pragma once

#include <memory>
#include <functional>
#include <mod/IModLoader.hpp>
#include <info/IApplicationInfo.hpp>
#include <game/controller/Buttons.hpp>

namespace CubA4::render::engine
{
	class IRenderManager;
}

namespace CubA4::system
{
	class IAppCallback
	{
	public:
		virtual std::function<std::shared_ptr<mod::IModLoader>()> getModLoaderFactory() const = 0;
		virtual std::shared_ptr<const CubA4::info::IApplicationInfo> getApplicationInfo() const = 0;
		virtual std::shared_ptr<render::engine::IRenderManager> getRenderManager() const = 0;
		virtual const render::IRenderInfo &getRenderInfo() const = 0;
		virtual std::pair<bool, CubA4::game::controller::BMods> getButtonState(CubA4::game::controller::Button btn) const = 0;
		virtual bool requestMouseCapture(bool enable) = 0;
	protected:
		virtual ~IAppCallback() = default;
		explicit IAppCallback() = default;
	private:
	};
}
