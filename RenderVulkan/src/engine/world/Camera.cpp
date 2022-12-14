#include <engine/world/Camera.hpp>
#include <algorithm>
#include <glm/gtc/constants.hpp>
#include <glm/common.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fmt/format.h>
using namespace CubA4::render::engine::world;

Camera::Camera()
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

void Camera::setPosition(float x, float y, float z, CubA4::world::ChunkPos chunkPos)
{
    x_ = x;
    y_ = y;
    z_ = z;
    chunkPos_ = chunkPos;
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
    const auto clampWith = [](float &coord, decltype(chunkPos_.x) &inChunk)
    {
        if (coord > CubA4::world::ChunkSize + 1)
        {
            coord -= CubA4::world::ChunkSize;
            inChunk++;
        }
        else if (coord < -1)
        {
            coord += CubA4::world::ChunkSize;
            inChunk--;
        }
    };
    if (local)
    {
        glm::vec3 direction;
        glm::vec3 move {x, y, z};
        direction.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
        direction.y = sin(glm::radians(pitch_));
        direction.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
        auto viewLook = glm::quatLookAt(glm::normalize(direction), {0, 1, 0});
        auto m = glm::toMat3(viewLook);
        move = m * move;
        x_ += move.x;
        y_ += move.y;
        z_ += move.z;
    }
    else
    {
        x_ += x;
        y_ += y;
        z_ += z;
    }
    auto chunkPosBefore = chunkPos_;
    auto xB = x_;
    auto yB = y_;
    auto zB = z_;
    
    clampWith(x_, chunkPos_.x);
    clampWith(y_, chunkPos_.y);
    clampWith(z_, chunkPos_.z);

    auto same = [](float a, float b) -> bool
    {
        auto diff = a - a;
        return (diff < 0.1) && (-diff < 0.1);
    };

    if (chunkPos_ != chunkPosBefore || !same(xB, x_) || !same(yB, y_) || !same(zB, z_))
    {
        std::cout << fmt::format("Before [{}, {}, {}] in chunk [{}, {}, {}]\n", xB, yB, zB, chunkPosBefore.x, chunkPosBefore.y, chunkPosBefore.z);
        std::cout << fmt::format("After [{}, {}, {}] in chunk [{}, {}, {}]\n", x_, y_, z_, chunkPos_.x, chunkPos_.y, chunkPos_.z);
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

const glm::mat4 &Camera::getViewMatrix() const
{
    return viewMatrix_;
}

const CubA4::world::ChunkPos &Camera::getChunkPos() const
{
    return chunkPos_;
}

void Camera::updateMatrix()
{
    if (!active_)
        return;
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    direction.y = sin(glm::radians(pitch_));
    direction.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    direction = glm::normalize(direction);
    viewMatrix_ = glm::lookAt({x_, y_, z_}, glm::vec3{x_, y_, z_} + direction, {0, 1, 0});
}