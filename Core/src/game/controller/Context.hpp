#pragma once

#include <string>
#include <unordered_set>
#include <game/controller/IContext.hpp>

namespace CubA4::game::controller
{
	class IContextCallback;

	class Context : public virtual IContext
	{
	public:
		Context(IContextCallback &callback);

		bool has(const std::string &context) const override;
		bool add(const std::string &context) override;
		bool remove(const std::string &context) override;
		void forceUpdate() override;
	private:
		std::unordered_set<std::string> context_;
		IContextCallback &callback_;
	};
}