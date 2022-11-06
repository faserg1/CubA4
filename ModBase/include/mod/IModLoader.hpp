#pragma once

#include <memory>
#include <functional>
#include <string>
#include <IModInfo.hpp>
#include <system/IEnvironmentBuilder.hpp>

namespace CubA4:: mod
{
	class IModLoader
	{
	public:
		virtual ~IModLoader() = default;
		using IEnvironmentBuilderFactory = std::function<std::shared_ptr<CubA4::system::IEnvironmentBuilder>(const CubA4::mod::IModInfo &modInfo)>;

		virtual void find() = 0;
		virtual void load() = 0;
		virtual void setup(IEnvironmentBuilderFactory builderFactory) = 0;
		virtual void shutdown() = 0;
		virtual void unload() = 0;
	protected:
		explicit IModLoader() = default;
	};
}
