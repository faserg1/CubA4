#pragma once

#include <memory>
#include <vector>

namespace CubA4::render::engine::model
{
	class IRenderModel;
}

namespace CubA4::object
{
	struct EntityBuilderData
	{
		std::shared_ptr<const CubA4::render::engine::model::IRenderModel> renderModel;
	};
}