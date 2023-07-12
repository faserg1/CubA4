#pragma once

#include <string>
#include <unordered_set>
#include <game/controller/IContext.hpp>

namespace CubA4::game::controller
{
	class Context : public virtual IContext
	{
	public:
		Context();

		bool has(const std::string &context) const override;
		bool add(const std::string &context) override;
		bool remove(const std::string &context) override;
	private:
		std::unordered_set<std::string> context_;
	};
}