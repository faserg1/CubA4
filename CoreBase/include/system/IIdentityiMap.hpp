#ifndef IIDENTITYIMAP_HPP
#define IIDENTITYIMAP_HPP

#include <string>
#include <functional>
#include <cstdint>

namespace CubA4
{
	namespace core
	{
		namespace system
		{
			class IIdentityiMap
			{
			public:
				virtual void clear() = 0;
				virtual int64_t add(const std::string &tag, const std::string &id) = 0;
				virtual int64_t get(const std::string &tag, const std::string &id) const = 0;
			protected:
				explicit IIdentityiMap() = default;
				virtual ~IIdentityiMap() = default;
			private:
			};
		}
	}
}

#endif // IIDENTITYIMAP_HPP
