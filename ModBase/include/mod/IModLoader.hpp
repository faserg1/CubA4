#ifndef IMODLOADER_HPP
#define IMODLOADER_HPP

#include <memory>
#include <functional>
#include <string>

namespace CubA4
{
	namespace core
	{
		namespace system
		{
			class IEnvironmentBuilder;
		}
	}

	namespace mod
	{
		class IModInfo;

		class IModLoader
		{
		public:
			virtual ~IModLoader() = default;
			using IEnvironmentBuilderFactory = std::function<std::shared_ptr<CubA4::core::system::IEnvironmentBuilder>(const CubA4::mod::IModInfo &modInfo)>;

			virtual void find() = 0;
			virtual void load() = 0;
			virtual void setup(IEnvironmentBuilderFactory builderFactory) = 0;
			virtual void shutdown() = 0;
			virtual void unload() = 0;
		protected:
			explicit IModLoader() = default;
		};
	}
}

#endif // IMODLOADER_HPP