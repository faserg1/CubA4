#pragma once

#include <memory>
#include <engine/world/ICamera.hpp>
#include <glm/glm.hpp>

namespace CubA4::render::engine::world
{
	class WorldManager;

	class Camera :
		public virtual ICamera,
		public std::enable_shared_from_this<Camera>
	{
	public:
		explicit Camera(std::weak_ptr<WorldManager> worldManager);
		~Camera();

		void setActive(bool active);
		CubA4::world::GlobalPosition getPosition() const override;
		void setPosition(CubA4::world::GlobalPosition position) override;
		void setRotation(float roll, float pitch, float yaw) override;
		void move(float x, float y, float z, bool local) override;
		void rotate(float roll, float pitch, float yaw) override;

		const glm::mat4 &getViewMatrix() const;
		const CubA4::world::ChunkPos &getChunkPos() const;

		Ray getRay(uint64_t x, uint64_t y) const override;
		Ray getRay() const override;
	protected:
		void updateMatrix();
		glm::vec3 calculateDirection() const;
	private:
		std::weak_ptr<WorldManager> worldManager_;
		bool active_ = false;

		float roll_ = 0;
		float pitch_ = 0;
		float yaw_ = 0;

		CubA4::world::GlobalPosition position_;
		glm::mat4 viewMatrix_ {};
	};
}
