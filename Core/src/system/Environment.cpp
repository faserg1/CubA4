#include "../../include/system/Environment.hpp"
using namespace CubA4::core::system;

Environment::Environment(EnvironmentContext &&context) :
	context_(std::move(context))
{
	
}

Environment::~Environment()
{
	
}

int64_t Environment::getId(const std::shared_ptr<const CubA4::mod::object::IObject> object) const
{
	auto iter = context_.getReverseObjectsMap().find(object);
	if (iter == context_.getReverseObjectsMap().end())
		return -1;
	return iter->second;
}