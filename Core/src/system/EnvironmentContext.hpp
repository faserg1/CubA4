#pragma once

#include <system/IdentityMap.hpp>
#include <object/IObject.hpp>
#include <map>

namespace CubA4::system
{
	class EnvironmentContext
	{
	public:
		using objectsMap_t = std::map<int64_t, std::shared_ptr<CubA4::object::IObject>>;
		using reverseObjectsMap_t = std::map<std::shared_ptr<const CubA4::object::IObject>, int64_t>;
		explicit EnvironmentContext(IdentityMap &&map, objectsMap_t &&objectsMap);
		explicit EnvironmentContext(EnvironmentContext &&context);
		~EnvironmentContext();

		const IdentityMap &getMap() const;
		const objectsMap_t &getObjectsMap() const;
		const reverseObjectsMap_t &getReverseObjectsMap() const;
	protected:
	private:
		const IdentityMap map_;
		const objectsMap_t objectsMap_;
		const reverseObjectsMap_t reverseObjectsMap_;
	private:
		reverseObjectsMap_t generateReverseMap(const objectsMap_t &objects);
	};
}
