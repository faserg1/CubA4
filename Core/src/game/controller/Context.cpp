#include <game/controller/Context.hpp>
using namespace CubA4::game::controller;

Context::Context() = default;

bool Context::has(const std::string &context) const
{
	return context_.contains(context);
}

bool Context::add(const std::string &context)
{
	if (has(context))
		return false;
	context_.insert(context);
	return true;
}

bool Context::remove(const std::string &context)
{
	if (!has(context))
		return false;
	context_.erase(context);
	return true;
}