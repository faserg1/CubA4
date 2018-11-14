#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <system/IEnvironment.hpp>
#include "EnvironmentContext.hpp"

namespace CubA4
{
	namespace core
	{
		namespace system
		{
			class Environment :
				public virtual IEnvironment
			{
			public:
				explicit Environment(EnvironmentContext &&context);
				~Environment();

				int64_t getId(const std::shared_ptr<const CubA4::mod::object::IObject> object) const;
			protected:
			private:
				const EnvironmentContext context_;
			};
		}
	}
}

#endif // ENVIRONMENT_HPP
