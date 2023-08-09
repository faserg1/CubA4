#pragma once

#include <memory>
#include <entities/IPlayerDefinition.hpp>
#include <engine/model/IRenderModel.hpp>

namespace CubA4::object
{
	class PlayerDefinition : public virtual IPlayerDefinition
	{
		using ModelType = CubA4::render::engine::model::IRenderModel;
	public:
		PlayerDefinition(std::shared_ptr<const ModelType> model);

		IdType getId() const override;
		std::wstring getName() const override;

		void onComponentStage(IEntityFactoryBuilder &builder) const override;
		void onRenderPrepareStage(IEntityRenderBuilder &builder) const override;
	private:
		std::shared_ptr<const ModelType> model_;
	};
}