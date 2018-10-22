#ifndef ENVIRONMENTBUILDERCONTEXT_HPP
#define ENVIRONMENTBUILDERCONTEXT_HPP

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
				explicit EnvironmentBuilderContext(std::shared_ptr<const CubA4::mod::IModInfo> modInfo);
				~EnvironmentBuilderContext();
			protected:
			private:
				const std::shared_ptr<const CubA4::mod::IModInfo> modInfo_;
			};
		}
	}
}

#endif // ENVIRONMENTBUILDERCONTEXT_HPP
