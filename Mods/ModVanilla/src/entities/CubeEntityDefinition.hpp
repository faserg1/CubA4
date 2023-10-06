#pragma once

#include <memory>
#include <entities/ICubeEntityDefinition.hpp>
#include <engine/model/IRenderModel.hpp>

namespace CubA4::physics
{
	class IPhysicsEntityDefinition;
}

namespace CubA4::object
{
	class CubeEntityDefinition : public virtual ICubeEntityDefinition
	{
		using ModelType = CubA4::render::engine::model::IRenderModel;
	public:
		CubeEntityDefinition(std::shared_ptr<const ModelType> model, std::shared_ptr<CubA4::physics::IPhysicsEntityDefinition> physicsDef);
		~CubeEntityDefinition();

		IdType getId() const override;
		std::wstring getName() const override;

		void onComponentStage(IEntityFactoryBuilder &builder) const override;
		void onRenderPrepareStage(IEntityRenderBuilder &builder) const override;
	private:
		std::shared_ptr<const ModelType> model_;
		std::shared_ptr<CubA4::physics::IPhysicsEntityDefinition> physicsDef_;
	};
}