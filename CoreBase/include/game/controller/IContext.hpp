#pragma once

#include <string>

namespace CubA4::game::controller
{
	class IContext
	{
	public:
		virtual ~IContext() = default;

		virtual bool has(const std::string &context) const = 0;
		virtual bool add(const std::string &context) = 0;
		virtual bool remove(const std::string &context) = 0;
		virtual void forceUpdate() = 0;
	protected:
		IContext() = default;
	};
}