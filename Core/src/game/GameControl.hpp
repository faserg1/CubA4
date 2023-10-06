#pragma once

#include <memory>
#include <Core.hpp>
#include <game/Game.hpp>
#include <game/IGameControl.hpp>
#include <world/WorldControl.hpp>
#include <physics/PhysicsEntityControl.hpp>

namespace CubA4::game
{
	class GameControl : public virtual IGameControl
	{
	public:
		GameControl(Core &core, CubA4::game::Game &game);
		bool requestWorldChange(const std::string &worldId, const std::string &dimId);
		CubA4::world::IWorldControl &getWorldControl() override;
		CubA4::physics::IPhysicsEntityControl &getPhysicsEntityControl() override;
		std::shared_ptr<object::IEntity> requestSpawn(std::shared_ptr<const object::IEntityFactory> factory, IdType dimensionId,
			const CubA4::world::GlobalPosition &pos) override;
		bool requestDespawn(const object::IEntity &entity) override;
	private:
		CubA4::Core &core_;
		CubA4::game::Game &game_;
		std::unique_ptr<CubA4::world::WorldControl> worldControl_;
		std::unique_ptr<CubA4::physics::PhysicsEntityControl> physicsEntityControl_;
	};
}