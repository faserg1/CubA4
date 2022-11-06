#pragma once

#include <memory>
#include <functional>
#include <mod/IModLoader.hpp>
#include <info/IApplicationInfo.hpp>

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
	protected:
		virtual ~IAppCallback() = default;
		explicit IAppCallback() = default;
	private:
	};
}
