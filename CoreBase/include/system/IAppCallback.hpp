#ifndef IAPPCALLBACK_HPP
#define IAPPCALLBACK_HPP

#include <memory>

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
		namespace system
		{
			class IAppCallback
			{
			public:
				virtual std::shared_ptr<mod::IModLoader> getModLoader() const = 0;
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

#endif // IAPPCALLBACK_HPP
