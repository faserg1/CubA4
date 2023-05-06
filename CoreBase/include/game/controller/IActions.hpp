#pragma once

#include <string>
#include <functional>
#include <memory>
#include <util/ISubscription.hpp>
#include <game/controller/Action.hpp>

namespace CubA4::game::controller
{
	class IActions
	{
	public:
		virtual ~IActions() = default;

		// TODO: ask for mod info?

		virtual [[nodiscard]] std::unique_ptr<util::ISubscription> addActionCallback(const std::string &action, std::function<void()> callbackOnce) = 0;
		virtual [[nodiscard]] std::unique_ptr<util::ISubscription> addActionAxisCallback(const std::string &action, std::function<void(int32_t, int32_t)> callbackAxis) = 0;
		virtual [[nodiscard]] std::unique_ptr<util::ISubscription> addActionPositionCallback(const std::string &action, std::function<void(int32_t, int32_t)> callbackAxis) = 0;
	protected:
		explicit IActions() = default;
	};
}
