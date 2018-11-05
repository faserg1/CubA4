#ifndef VERSIONDEPENDENCY_HPP
#define VERSIONDEPENDENCY_HPP

#include <info/IVersionDependency.hpp>
#include "Version.hpp"

namespace CubA4
{
	namespace core
	{
		namespace info
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
	}
}

#endif // VERSIONDEPENDENCY_HPP
