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
	protected:
		virtual ~IAppCallback() = default;
		explicit IAppCallback() = default;
	private:
	};
}
