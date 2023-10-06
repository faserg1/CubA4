#pragma once

#include <string>
#include <functional>
#include <memory>
#include <game/controller/IActions.hpp>
#include <game/controller/IContextActionsRules.hpp>
#include <game/controller/IActionsHandler.hpp>

namespace CubA4::game::controller
{
	class IContextActions
	{
	public:
		virtual ~IContextActions() = default;

		virtual void addActionCallback(const std::string &action, std::function<void()> callbackOnce) = 0;
		virtual void addActionAxisCallback(const std::string &action, std::function<void(int32_t, int32_t)> callbackAxis) = 0;
		virtual void addActionPositionCallback(const std::string &action, std::function<void(int32_t, int32_t)> callbackAxis) = 0;
		virtual void addActionPositionMoveCallback(const std::string &action, std::function<void(int32_t, int32_t)> callbackAxis) = 0;
		virtual void addHandler(std::shared_ptr<IActionsHandler> handler) = 0;
		virtual bool getActionState(const std::string &action) const = 0;
		virtual void requestContextCheck() = 0;
	protected:
		IContextActions() = default;
	};
}