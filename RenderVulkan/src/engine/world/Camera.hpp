#pragma once

#include <engine/world/ICamera.hpp>
#include <glm/glm.hpp>

namespace CubA4::render::engine::world
{
	class Camera :
		public virtual ICamera
	{
	public:
		explicit Camera();
		~Camera();

		void setActive(bool active);
		void setPosition(CubA4::world::GlobalPosition position) override;
		void setRotation(float roll, float pitch, float yaw) override;
		void move(float x, float y, float z, bool local) override;
		void rotate(float roll, float pitch, float yaw) override;

		const glm::mat4 &getViewMatrix() const;
		const CubA4::world::ChunkPos &getChunkPos() const;
	protected:
		void updateMatrix();
	private:
		bool active_ = false;

		float roll_ = 0;
		float pitch_ = 0;
		float yaw_ = 0;

		CubA4::world::GlobalPosition position_;
		glm::mat4 viewMatrix_ {};
	};
}
