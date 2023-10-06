#include <game/controller/Context.hpp>
#include <game/controller/IContextCallback.hpp>
using namespace CubA4::game::controller;

Context::Context(IContextCallback &callback) :
	callback_(callback)
{

}

bool Context::has(const std::string &context) const
{
	return context_.contains(context);
}

bool Context::add(const std::string &context)
{
	if (has(context))
		return false;
	context_.insert(context);
	callback_.onContextChanged();
	return true;
}

bool Context::remove(const std::string &context)
{
	if (!has(context))
		return false;
	context_.erase(context);
	callback_.onContextChanged();
	return true;
}

void Context::forceUpdate()
{
	callback_.onContextChanged();
}