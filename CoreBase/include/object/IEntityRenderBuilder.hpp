#pragma once

#include <memory>

namespace CubA4::render::engine::model
{
	class IRenderModel;
}

namespace CubA4::object
{
	class IEntityRenderBuilder
	{
	public:
		virtual ~IEntityRenderBuilder() = default;

		virtual IEntityRenderBuilder &addModel(std::shared_ptr<const CubA4::render::engine::model::IRenderModel> model) = 0;
	protected:
		explicit IEntityRenderBuilder() = default;
	};
}
