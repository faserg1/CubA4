#pragma once

#include <info/IVersionDependency.hpp>
#include <info/Version.hpp>

namespace CubA4::info
{
	class VersionDependency :
		public virtual IVersionDependency
	{
	public:
		explicit VersionDependency(const IVersion &required, const IVersion &prefered);
		~VersionDependency();

		const IVersion &required() const override;
		const IVersion &prefered() const override;
	protected:
	private:
		const Version required_;
		const Version prefered_;
	};
}

