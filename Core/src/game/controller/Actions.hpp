#pragma once

#include <game/controller/IActions.hpp>

namespace CubA4::game::controller
{
	class Actions : public virtual IActions
	{
		friend class Subscription;
		struct Callback;
	public:
		explicit Actions();
		~Actions();

		std::unique_ptr<util::ISubscription> addActionCallback(const std::string &action, std::function<void()> callbackOnce) override;
		std::unique_ptr<util::ISubscription> addActionCallback(const std::string &action, std::function<void(int32_t)> callbackAxis) override;

		void onAction(const std::string &action);
		void onAxisAction(const std::string &action, int32_t axis);

		const std::unordered_map<std::string, std::vector<Callback>> &getCallbacks() const;
	private:
		void addActionCallback(const std::string &action, Callback callback);
	private:
		struct Callback
		{
			uint64_t id;
			std::function<void()> callbackOnce;
			std::function<void(int32_t)> callbackAxis;

			void operator()() const { if (callbackOnce) callbackOnce(); }
			void operator()(int32_t axis) const {if (callbackAxis) callbackAxis(axis); }
		};
		class Subscription : public virtual util::ISubscription
		{
		public:
			Subscription(Actions *actions, const std::string &action, uint64_t id);
			~Subscription();
			void unsubscribe() override;
		private:
			Actions *const actions_;
			const std::string action_;
			const uint64_t id_;
		};
		std::unordered_map<std::string, std::vector<Callback>> callbacks_;
		uint64_t idCounter_ = 0;
	};
}
