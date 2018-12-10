#ifndef COREBASE_IVERSIONDEPENDENCY_HPP
#define COREBASE_IVERSIONDEPENDENCY_HPP

namespace CubA4
{
	namespace core
	{
		namespace info
		{
			class IVersion;

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
	}
}

#endif // COREBASE_IVERSIONDEPENDENCY_HPP
