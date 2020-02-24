#ifndef COREBASE_IAPPCALLBACK_HPP
#define COREBASE_IAPPCALLBACK_HPP

#include <memory>
#include <functional>

namespace CubA4
{
	namespace mod
	{
		class IModLoader;
	}

	namespace render
	{
		class IRenderInfo;

		namespace engine
		{
			class IRenderManager;
		}
	}

	namespace core
	{
		namespace info
		{
			class IApplicationInfo;
		}

		namespace system
		{
			class IAppCallback
			{
			public:
				virtual std::function<std::shared_ptr<mod::IModLoader>()> getModLoaderFactory() const = 0;
				virtual std::shared_ptr<const CubA4::core::info::IApplicationInfo> getApplicationInfo() const = 0;
				virtual std::shared_ptr<render::engine::IRenderManager> getRenderManager() const = 0;
				virtual const render::IRenderInfo &getRenderInfo() const = 0;
			protected:
				virtual ~IAppCallback() = default;
				explicit IAppCallback() = default;
			private:
			};
		}
	}
}

#endif // COREBASE_IAPPCALLBACK_HPP
