#pragma once

#include <string>
#include <functional>
#include <memory>
#include <util/ISubscription.hpp>

namespace CubA4::game::controller
{
	class IActions
	{
	public:
		virtual ~IActions() = default;

		// todo: ask for mod info?

		virtual [[nodiscard]] std::unique_ptr<util::ISubscription> addActionCallback(const std::string &action, std::function<void()> callbackOnce) = 0;
		virtual [[nodiscard]] std::unique_ptr<util::ISubscription> addActionCallback(const std::string &action, std::function<void(int32_t)> callbackAxis) = 0;
	protected:
		explicit IActions() = default;
	};
}
