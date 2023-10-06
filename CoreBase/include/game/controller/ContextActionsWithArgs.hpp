#pragma once

#include <string>
#include <functional>
#include <memory>
#include <tuple>
#include <vector>
#include <game/controller/IActions.hpp>
#include <game/controller/IContextActions.hpp>

namespace CubA4::game::controller
{
	template <class ...Args>
	class ContextActionsWithArgs
	{
	public:
		virtual ~ContextActionsWithArgs() = default;
		ContextActionsWithArgs(std::shared_ptr<IContextActions> actions, std::tuple<Args...> args) :
			actions_(actions), args_(args)
		{

		}

		void addActionCallback(const std::string &action, std::function<void(Args ...)> callbackOnce)
		{
			actions_->addActionCallback(action, [this, callbackOnce]()
			{
				std::apply(callbackOnce, args_);
			});
		}
		void addActionAxisCallback(const std::string &action, std::function<void(int32_t, int32_t, Args...)> callbackAxis)
		{
			actions_->addActionAxisCallback(action, [this, callbackAxis](int32_t x, int32_t y)
			{
				auto func = [this, callbackAxis, x, y](Args ...args)
				{
					callbackAxis(x, y, args...);
				};
				std::apply(func, args_);
			});
		}
		void addActionPositionCallback(const std::string &action, std::function<void(int32_t, int32_t, Args...)> callbackPosition)
		{
			actions_->addActionPositionCallback(action, [this, callbackPosition](int32_t x, int32_t y)
			{
				std::apply([this, callbackPosition, x, y](Args ...args)
				{
					callbackPosition(x, y, args...);
				}, args_);
			});
		}
		void addActionPositionMoveCallback(const std::string &action, std::function<void(int32_t, int32_t, Args ...)> callbackMove)
		{
			actions_->addActionPositionMoveCallback(action, [this, callbackMove](int32_t x, int32_t y)
			{
				std::apply([this, callbackMove, x, y](Args ...args)
				{
					callbackMove(x, y, args...);
				}, args_);
			});
		}
		void addHandler(std::shared_ptr<IActionsHandlerArgs<Args...>> handler)
		{
			class ActionHandlerWrapper : public virtual IActionsHandler
			{
			public:
				ActionHandlerWrapper(std::shared_ptr<IActionsHandlerArgs<Args...>> handler, const std::tuple<Args...> &args) :
					innerHandler_(handler), args_(args)
				{
				}

				void onAction(const std::string &action) override
				{
					std::apply([this, action](Args ...args)
					{
						innerHandler_->onAction(action, args...);
					}, args_);
				}
				void onActionAxis(const std::string &action, int32_t x, int32_t y) override
				{
					std::apply([this, action, x, y](Args ...args)
					{
						innerHandler_->onActionAxis(action, x, y, args...);
					}, args_);
				}
				void onActionPosition(const std::string &action, int32_t x, int32_t y) override
				{
					std::apply([this, action, x, y](Args ...args)
					{
						innerHandler_->onActionPosition(action, x, y, args...);
					}, args_);
				}
				void onActionPositionMove(const std::string &action, int32_t x, int32_t y) override
				{
					std::apply([this, action, x, y](Args ...args)
					{
						innerHandler_->onActionPositionMove(action, x, y, args...);
					}, args_);
				}
			private:
				const std::shared_ptr<IActionsHandlerArgs<Args...>> innerHandler_;
				const std::tuple<Args...> &args_;
			};
			auto wrapper = std::make_shared<ActionHandlerWrapper>(handler, args_);
			actions_->addHandler(wrapper);
		}

		// TODO: check action?
		void requestContextCheck()
		{
			actions_->requestContextCheck();
		}
	private:
		const std::shared_ptr<IContextActions> actions_;
		const std::tuple<Args...> args_;
		std::vector<std::shared_ptr<IActionsHandlerArgs<Args...>>> actionHandlers_;
	};
}