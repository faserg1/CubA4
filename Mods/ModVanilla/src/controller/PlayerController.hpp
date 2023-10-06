#pragma once

#include <object/EntityControllerTypes.hpp>

namespace CubA4::object
{
	class PlayerController : public IEntityContextActions
	{
	public:
		void onAction(const std::string &action, EntityArg entity) override;
		void onActionAxis(const std::string &action, int32_t x, int32_t y, EntityArg entity) override;
		void onActionPosition(const std::string &action, int32_t x, int32_t y, EntityArg entity) override;
		void onActionPositionMove(const std::string &action, int32_t x, int32_t y, EntityArg entity) override;
	};
}