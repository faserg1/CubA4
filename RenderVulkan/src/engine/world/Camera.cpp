#include <engine/world/Camera.hpp>
#include <engine/world/WorldManager.hpp>
#include <algorithm>
#include <glm/gtc/constants.hpp>
#include <glm/common.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fmt/format.h>
using namespace CubA4::render::engine::world;

constexpr const glm::vec3 up {0, 1, 0};

Camera::Camera(std::weak_ptr<WorldManager> worldManager):
	worldManager_(worldManager)
{
	
}

Camera::~Camera()
{
	
}

void Camera::setActive(bool active)
{
    active_ = active;
    updateMatrix();
}

CubA4::world::GlobalPosition Camera::getPosition() const
{
	return position_;
}

void Camera::setPosition(CubA4::world::GlobalPosition position)
{
    position_ = position;
    updateMatrix();
}

void Camera::setRotation(float roll, float pitch, float yaw)
{
    roll_ = roll;
    pitch_ = pitch;
    yaw_ = yaw;
    updateMatrix();
}

void Camera::move(float x, float y, float z, bool local)
{
    if (local)
    {
		z *= -1;
        glm::vec3 move {x, y, z};
        auto direction = calculateDirection();
        auto viewLook = glm::quatLookAtRH(direction, up);
        auto m = glm::toMat3(viewLook);
        move = m * move;
		if (move.length())
        	position_ += CubA4::world::BasePos<float>{move.x, move.y, move.z};
    }
    else
    {
        position_ += CubA4::world::BasePos<float>{x, y, z};
    }
    updateMatrix();
}

void Camera::rotate(float roll, float pitch, float yaw)
{
    roll_ += roll;
    pitch_ += pitch;
    yaw_ += yaw;
    if (yaw_ > 360.f)
        yaw_ -= 360.f;
    else if (yaw_ < -360.f)
        yaw += 360.f;
    pitch_ = std::clamp(pitch_, -89.f, 89.f);
    updateMatrix();
}

Ray Camera::getRay(uint64_t x, uint64_t y) const
{
	auto wm = worldManager_.lock();
	if (!wm)
		return {};
	return wm->getRayFrom(x, y, shared_from_this());
}

Ray Camera::getRay() const
{
	auto wm = worldManager_.lock();
	if (!wm)
		return {};
	return wm->getRayFrom(shared_from_this());
}

const glm::mat4 &Camera::getViewMatrix() const
{
    return viewMatrix_;
}

const CubA4::world::ChunkPos &Camera::getChunkPos() const
{
    return position_.chunkPos();
}

void Camera::updateMatrix()
{
    if (!active_)
        return;
    auto direction = calculateDirection();
    auto &[bx, by, bz] = position_.blockPosition();
    auto &[x, y, z] = position_.inBlockPos();
    auto pos = glm::vec3{bx + x, by + y, bz + z};
    viewMatrix_ = glm::lookAtRH(pos, pos + direction, up);
}

glm::vec3 Camera::calculateDirection() const
{
	glm::vec3 direction;
    direction.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    direction.y = sin(glm::radians(pitch_));
    direction.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    direction = glm::normalize(direction);
	return direction;
}