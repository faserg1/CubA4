#pragma once

#include <info/IVersion.hpp>

namespace CubA4::info
{
	class IVersionDependency
	{
	public:
		virtual const IVersion &required() const = 0;
		virtual const IVersion &prefered() const = 0;
	protected:
		explicit IVersionDependency() = default;
		virtual ~IVersionDependency() = default;
	private:
	};
}

