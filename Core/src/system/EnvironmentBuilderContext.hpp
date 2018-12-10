#ifndef CORE_ENVIRONMENTBUILDERCONTEXT_HPP
#define CORE_ENVIRONMENTBUILDERCONTEXT_HPP

#include <memory>

namespace CubA4
{
	namespace mod
	{
		class IModInfo;
	}

	namespace core
	{
		namespace system
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
	}
}

#endif // CORE_ENVIRONMENTBUILDERCONTEXT_HPP
