#include "EnvironmentContext.hpp"
using namespace CubA4::core::system;

EnvironmentContext::EnvironmentContext(IdentityMap &&map, objectsMap_t &&objectsMap) :
	map_(std::move(map)),
	objectsMap_(objectsMap),
	reverseObjectsMap_(std::move(generateReverseMap(objectsMap_)))
{
	
}

EnvironmentContext::EnvironmentContext(EnvironmentContext &&context) :
	map_(std::move(context.map_)),
	objectsMap_(std::move(context.objectsMap_)),
	reverseObjectsMap_(std::move(context.reverseObjectsMap_))
{

}

EnvironmentContext::~EnvironmentContext()
{
	
}

const IdentityMap &EnvironmentContext::getMap() const
{
	return map_;
}

const EnvironmentContext::objectsMap_t &EnvironmentContext::getObjectsMap() const
{
	return objectsMap_;
}

const EnvironmentContext::reverseObjectsMap_t &EnvironmentContext::getReverseObjectsMap() const
{
	return reverseObjectsMap_;
}

EnvironmentContext::reverseObjectsMap_t EnvironmentContext::generateReverseMap(const objectsMap_t &objects)
{
	reverseObjectsMap_t reverseMap;
	for (auto &pair : objects)
		reverseMap.insert(std::make_pair(pair.second, pair.first));
	return std::move(reverseMap);
}