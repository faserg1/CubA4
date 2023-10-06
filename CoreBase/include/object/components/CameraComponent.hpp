#pragma once

#include <memory>
#include <engine/world/ICamera.hpp>

namespace CubA4::object
{
	struct CameraComponent
	{
		const std::shared_ptr<CubA4::render::engine::world::ICamera> camera;
	};
}

