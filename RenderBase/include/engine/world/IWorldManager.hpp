#pragma once

#include <cstdint>
#include <memory>
#include <world/IChunk.hpp>
#include <engine/world/ICamera.hpp>

namespace CubA4::render::engine::world
{
	class IWorldManager
	{
	public:
		virtual std::shared_ptr<ICamera> createCamera() = 0;
		virtual void setActiveCamera(std::shared_ptr<ICamera> camera) = 0;
		virtual void setFieldOfView(float degrees) = 0;
	protected:
		explicit IWorldManager() = default;
		virtual ~IWorldManager() = default;
	private:
	};
}


