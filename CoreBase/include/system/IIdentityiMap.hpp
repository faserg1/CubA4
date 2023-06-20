#pragma once

#include <string>
#include <functional>
#include <cstdint>

namespace CubA4::system
{
	class IIdentityiMap
	{
	public:
		using IdType = int64_t;
	public:
		virtual void clear() = 0;
		virtual IdType add(const std::string &tag, const std::string &id) = 0;
		virtual IdType get(const std::string &tag, const std::string &id) const = 0;
		virtual IdType get(const std::string &fullId) const = 0;
		virtual std::string get(IdType id) const = 0;
	protected:
		explicit IIdentityiMap() = default;
		virtual ~IIdentityiMap() = default;
	private:
	};
}
