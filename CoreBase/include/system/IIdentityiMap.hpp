#ifndef COREBASE_IIDENTITYIMAP_HPP
#define COREBASE_IIDENTITYIMAP_HPP

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
				virtual int64_t get(const std::string &fullId) const = 0;
				virtual std::string get(int64_t id) const = 0;
			protected:
				explicit IIdentityiMap() = default;
				virtual ~IIdentityiMap() = default;
			private:
			};
		}
	}
}

#endif // COREBASE_IIDENTITYIMAP_HPP
