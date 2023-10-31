#pragma once

#include <cstdint>
#include <memory>
#include <world/IChunk.hpp>
#include <engine/world/ICamera.hpp>
#include <engine/world/Ray.hpp>

namespace CubA4::render::engine::world
{

	class IWorldManager
	{
	public:
		virtual std::shared_ptr<ICamera> createCamera() = 0;
		virtual void setActiveCamera(std::shared_ptr<ICamera> camera) = 0;
		virtual void setFieldOfView(float degrees) = 0;

		virtual Ray getRayFrom(uint64_t x, uint64_t y, std::shared_ptr<const ICamera> camera = {}) const = 0;
		virtual Ray getRayFrom(std::shared_ptr<const ICamera> camera = {}) const = 0;
	protected:
		explicit IWorldManager() = default;
		virtual ~IWorldManager() = default;
	private:
	};
}


