#pragma once

#include <game/controller/IActions.hpp>
#include <memory>

namespace CubA4::game::controller
{
	class Actions : public virtual IActions, public std::enable_shared_from_this<Actions>
	{
		friend class Subscription;
		struct Callback;
	public:
		explicit Actions();
		~Actions();

		std::unique_ptr<util::ISubscription> addActionCallback(const std::string &action, std::function<void()> callbackOnce) override;
		std::unique_ptr<util::ISubscription> addActionAxisCallback(const std::string &action, std::function<void(int32_t, int32_t)> callbackAxis) override;
		std::unique_ptr<util::ISubscription> addActionPositionCallback(const std::string &action, std::function<void(int32_t, int32_t)> callbackPosition) override;

		void onAction(const std::string &action);
		void onAxisAction(const std::string &action, int32_t axisX, int32_t axisY);
		void onPositionAction(const std::string &action, int32_t axisX, int32_t axisY);

		const std::unordered_map<std::string, std::vector<Callback>> &getCallbacks() const;
	private:
		void addActionCallback(const std::string &action, Callback callback);
	private:
		struct Callback
		{
			uint64_t id;
			std::function<void()> callbackOnce;
			std::function<void(int32_t, int32_t)> callbackAxis;

			void operator()() const { if (callbackOnce) callbackOnce(); }
			void operator()(int32_t axisX, int32_t axisY) const {if (callbackAxis) callbackAxis(axisX, axisY); }
		};
		class Subscription : public virtual util::ISubscription
		{
		public:
			Subscription(std::shared_ptr<Actions> actions, const std::string &action, uint64_t id);
			~Subscription();
			void unsubscribe() override;
		private:
			const std::weak_ptr<Actions> actions_;
			const std::string action_;
			const uint64_t id_;
		};
		std::unordered_map<std::string, std::vector<Callback>> callbacks_;
		uint64_t idCounter_ = 0;
	};
}
