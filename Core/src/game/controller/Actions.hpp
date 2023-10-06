#pragma once

#include <game/controller/IActions.hpp>
#include <memory>

namespace CubA4::game::controller
{
	class IController;

	class Actions :
		public virtual IActions,
		public std::enable_shared_from_this<Actions>,
		public virtual IActionsHandler
	{
		friend class SubscriptionSingle;
		friend class SubscriptionMulti;
		struct Callback;
	public:
		explicit Actions(IController *controller);
		~Actions();

		[[nodiscard]] std::unique_ptr<util::ISubscription> addActionCallback(const std::string &action, std::function<void()> callbackOnce) override;
		[[nodiscard]] std::unique_ptr<util::ISubscription> addActionAxisCallback(const std::string &action, std::function<void(int32_t, int32_t)> callbackAxis) override;
		[[nodiscard]] std::unique_ptr<util::ISubscription> addActionPositionCallback(const std::string &action, std::function<void(int32_t, int32_t)> callbackPosition) override;
		[[nodiscard]] std::unique_ptr<util::ISubscription> addActionPositionMoveCallback(const std::string &action, std::function<void(int32_t, int32_t)> callbackPosition) override;
		void addHandler(std::weak_ptr<IActionsHandler> handler) override;
		bool getActionState(const std::string &action) const override;
		void requestContextCheck() override;

		void onAction(const std::string &action) override;
		void onActionAxis(const std::string &action, int32_t x, int32_t y) override;
		void onActionPosition(const std::string &action, int32_t x, int32_t y) override;
		void onActionPositionMove(const std::string &action, int32_t x, int32_t y) override;

		const std::unordered_map<std::string, std::vector<Callback>> &getCallbacks() const;
	private:
		void addActionCallback(const std::string &action, Callback callback);
	protected:
		IController * const controller_;
	private:
		struct Callback
		{
			uint64_t id;
			std::function<void()> callbackOnce;
			std::function<void(int32_t, int32_t)> callbackAxis;

			void operator()() const { if (callbackOnce) callbackOnce(); }
			void operator()(int32_t axisX, int32_t axisY) const {if (callbackAxis) callbackAxis(axisX, axisY); }
		};
		class SubscriptionSingle : public virtual util::ISubscription
		{
		public:
			SubscriptionSingle(std::weak_ptr<Actions> actions, const std::string &action, uint64_t id);
			~SubscriptionSingle();
			void unsubscribe() override;
		private:
			const std::weak_ptr<Actions> actions_;
			const std::string action_;
			const uint64_t id_;
		};
		std::unordered_map<std::string, std::vector<Callback>> callbacks_;
		std::unordered_map<uint64_t, std::weak_ptr<IActionsHandler>> actionHandlers_;
		uint64_t idCounter_ = 0;
	};
}
