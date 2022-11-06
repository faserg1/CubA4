#include <system/Environment.hpp>
using namespace CubA4::system;

Environment::Environment(EnvironmentContext &&context) :
	context_(std::move(context))
{
	
}

Environment::~Environment()
{
	
}

int64_t Environment::getId(const std::shared_ptr<const CubA4::object::IObject> object) const
{
	auto iter = context_.getReverseObjectsMap().find(object);
	if (iter == context_.getReverseObjectsMap().end())
		return -1;
	return iter->second;
}

std::string Environment::getIdName(const std::shared_ptr<const CubA4::object::IObject> object) const
{
	return context_.getMap().get(getId(object));
}

std::shared_ptr<const CubA4::object::IObject> Environment::getObject(int64_t id) const
{
	auto iter = context_.getObjectsMap().find(id);
	if (iter == context_.getObjectsMap().end())
		return {};
	return iter->second;
}

std::shared_ptr<const CubA4::object::IObject> Environment::getObject(const std::string &id) const
{
	return getObject(context_.getMap().get(id));
}
