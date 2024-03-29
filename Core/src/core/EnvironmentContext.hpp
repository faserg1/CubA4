#pragma once

#include <core/IdentityMap.hpp>
#include <object/IObject.hpp>
#include <unordered_map>

namespace CubA4::core
{
	class EnvironmentContext
	{
	public:
		using objectsMap_t = std::unordered_map<int64_t, std::shared_ptr<CubA4::object::IObject>>;
		using reverseObjectsMap_t = std::unordered_map<const CubA4::object::IObject*, int64_t>;
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
