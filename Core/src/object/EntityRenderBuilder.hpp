#pragma once

#include <object/IEntityRenderBuilder.hpp>
#include <vector>

namespace CubA4::object
{
	struct EntityBuilderData;

	class EntityRenderBuilder : public virtual IEntityRenderBuilder
	{
	public:
		EntityRenderBuilder(EntityBuilderData &data);
		IEntityRenderBuilder &addModel(std::shared_ptr<const CubA4::render::engine::model::IRenderModel> model) override;
	private:
		EntityBuilderData &data_;
	};
}