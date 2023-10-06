#pragma once

#include <string>

namespace CubA4::game::controller
{
	template <class ...Args>
	class IActionsHandlerArgs
	{
	public:
		virtual ~IActionsHandlerArgs() = default;

		virtual void onAction(const std::string &action, Args... args) {}
		virtual void onActionAxis(const std::string &action, int32_t x, int32_t y, Args... args) {}
		virtual void onActionPosition(const std::string &action, int32_t x, int32_t y, Args... args) {}
		virtual void onActionPositionMove(const std::string &action, int32_t x, int32_t y, Args... args) {}
	protected:
		IActionsHandlerArgs() = default;
	};

	using IActionsHandler = IActionsHandlerArgs<>;
}