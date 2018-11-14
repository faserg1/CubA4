#ifndef ENVIRONMENTCONTEXT_HPP
#define ENVIRONMENTCONTEXT_HPP

#include "IdentityMap.hpp"
#include <map>

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
			class EnvironmentContext
			{
			public:
				using objectsMap_t = std::map<int64_t, const std::shared_ptr<const CubA4::mod::object::IObject>>;
				using reverseObjectsMap_t = std::map<const std::shared_ptr<const CubA4::mod::object::IObject>, int64_t>;
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
	}
}

#endif // ENVIRONMENTCONTEXT_HPP
