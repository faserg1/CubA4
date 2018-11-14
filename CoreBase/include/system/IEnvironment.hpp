#ifndef IENVIRONMENT_HPP
#define IENVIRONMENT_HPP

#include <cstdint>
#include <memory>

namespace CubA4
{
	namespace mod
	{
		namespace object
		{
			class IObject;
		}
	}

	namespace core
	{
		namespace system
		{
			class IEnvironment
			{
			public:
				virtual int64_t getId(const std::shared_ptr<const CubA4::mod::object::IObject> object) const = 0;
			protected:
				explicit IEnvironment() = default;
				virtual ~IEnvironment() = default;
			private:
			};
		}
	}
}

#endif // IENVIRONMENT_HPP
