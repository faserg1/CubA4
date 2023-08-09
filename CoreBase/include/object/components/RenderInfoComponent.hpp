#pragma once

#include <memory>

namespace CubA4::render::engine::model
{
	class IRenderModel;
}

namespace CubA4::object
{
	struct RenderInfoComponent
	{
		std::shared_ptr<const CubA4::render::engine::model::IRenderModel> renderModel;
	};
}