#pragma once

#include <memory>
#include <game/controller/IContext.hpp>

namespace CubA4::game::controller
{
	/// @brief Shloud be implemented by user
	class IContextActionsRules
	{
	public:
		virtual ~IContextActionsRules() = default;

		/// @brief Called, when context changes.
		/// @return Enabled in current context?
		virtual bool checkContext(const IContext &context) const = 0;
	protected:
		IContextActionsRules() = default;
	};
}