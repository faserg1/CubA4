#pragma once

#include <memory>
#include <object/EntityControllerTypes.hpp>

namespace CubA4
{
	class ICore;
}

namespace CubA4::mod
{
	class ModControl;
}

namespace CubA4::render::engine::debug
{
	class IRenderDebugCollection;
}

namespace CubA4::object
{
	class PlayerController : public IEntityContextActions
	{
	public:
		PlayerController(std::shared_ptr<const CubA4::ICore> core, std::shared_ptr<const CubA4::mod::ModControl> modControl);
		void onAction(const std::string &action, EntityArg entity) override;
		void onActionAxis(const std::string &action, int32_t x, int32_t y, EntityArg entity) override;
		void onActionPosition(const std::string &action, int32_t x, int32_t y, EntityArg entity) override;
		void onActionPositionMove(const std::string &action, int32_t x, int32_t y, EntityArg entity) override;
	private:
		void checkMovements(const std::string &action, std::shared_ptr<IEntity> player);
		void checkMain(const std::string &action, std::shared_ptr<IEntity> player);
	private:
		std::shared_ptr<const CubA4::ICore> core_;
		const std::shared_ptr<const CubA4::mod::ModControl> modControl_;
		std::shared_ptr<CubA4::render::engine::debug::IRenderDebugCollection> debugBlock_;
	};
}