#ifndef IVERSIONDEPENDENCY_HPP
#define IVERSIONDEPENDENCY_HPP

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

#endif // IVERSIONDEPENDENCY_HPP
