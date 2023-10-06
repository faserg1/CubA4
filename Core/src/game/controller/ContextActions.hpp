#pragma once

#include <game/controller/IContextActions.hpp>
#include <game/controller/IContext.hpp>
#include <game/controller/IActions.hpp>
#include <memory>
#include <vector>
#include <unordered_map>

namespace CubA4::game::controller
{
	class ContextActions :
		public virtual IContextActions,
		public virtual IActionsHandler,
		public std::enable_shared_from_this<ContextActions>
	{
		struct Callbacks;
	public:
		ContextActions(std::unique_ptr<IContextActionsRules> &&rules, std::shared_ptr<IActions> actions);
		void addActionCallback(const std::string &action, std::function<void()> callbackOnce) override;
		void addActionAxisCallback(const std::string &action, std::function<void(int32_t, int32_t)> callbackAxis) override;
		void addActionPositionCallback(const std::string &action, std::function<void(int32_t, int32_t)> callbackAxis) override;
		void addActionPositionMoveCallback(const std::string &action, std::function<void(int32_t, int32_t)> callbackAxis) override;
		void addHandler(std::shared_ptr<IActionsHandler> handler) override;
		bool getActionState(const std::string &action) const override;
		void requestContextCheck() override;

		void onContextChanged(const IContext &context);
	protected:
		void onAction(const std::string &action) override;
		void onActionAxis(const std::string &action, int32_t x, int32_t y) override;
		void onActionPosition(const std::string &action, int32_t x, int32_t y) override;
		void onActionPositionMove(const std::string &action, int32_t x, int32_t y) override;
	private:
		Callbacks *getCallback(const std::string &action, bool addIfNotExists = false);
	private:
		std::unique_ptr<IContextActionsRules> rules_;
		std::weak_ptr<IActions> actions_;
		struct Callbacks {
			std::vector<std::function<void()>> once;
			std::vector<std::function<void(int32_t, int32_t)>> axis;
			std::vector<std::function<void(int32_t, int32_t)>> position;
			std::vector<std::function<void(int32_t, int32_t)>> positionMove;
		};
		std::vector<std::shared_ptr<IActionsHandler>> actionHandlers_;
		
		std::unordered_map<std::string, Callbacks> callbacks_;
		
		bool enabled_ = false;
	};
}