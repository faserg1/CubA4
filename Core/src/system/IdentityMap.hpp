#ifndef IDENTITYMAP_HPP
#define IDENTITYMAP_HPP

#include <system/IIdentityiMap.hpp>
#include <boost/bimap.hpp>

namespace CubA4
{
	namespace core
	{
		namespace system
		{
			class IdentityMap :
				public virtual IIdentityiMap
			{
			public:
				explicit IdentityMap();
				explicit IdentityMap(IdentityMap &&other);
				explicit IdentityMap(const IdentityMap &&other);
				~IdentityMap();

				void clear() override;
				int64_t add(const std::string &tag, const std::string &id) override;
				int64_t get(const std::string &tag, const std::string &id) const override;
				int64_t get(const std::string &fullId) const override;
				std::string get(int64_t id) const override;
			protected:
			private:
				int64_t counter_;
				boost::bimap<int64_t, std::string> map_;
				using bm_value = decltype(map_)::value_type;
			private:
				static bool parseId(const std::string &input, std::string &tag, std::string &id);
				static std::string makeId(const std::string &tag, const std::string &id);
			};
		}
	}
}

#endif // IDENTITYMAP_HPP
