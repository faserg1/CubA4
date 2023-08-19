#pragma once

#include <memory>
#include <IModInfo.hpp>

namespace CubA4::core
{
	class EnvironmentBuilderContext
	{
		friend class EnvironmentBuilder;
	public:
		explicit EnvironmentBuilderContext(const CubA4::mod::IModInfo &modInfo);
		~EnvironmentBuilderContext();
	protected:
	private:
		const CubA4::mod::IModInfo &modInfo_;
	};
}
