#pragma once

#include <system/IIdentityiMap.hpp>
#include <boost/bimap.hpp>

namespace CubA4::system
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
		IdType add(const std::string &tag, const std::string &id) override;
		IdType get(const std::string &tag, const std::string &id) const override;
		IdType get(const std::string &fullId) const override;
		std::string get(IdType id) const override;
	protected:
	private:
		IdType counter_;
		boost::bimap<IdType, std::string> map_;
		using bm_value = decltype(map_)::value_type;
	private:
		static bool parseId(const std::string &input, std::string &tag, std::string &id);
		static std::string makeId(const std::string &tag, const std::string &id);
	};
}
