#pragma once

#include <memory>
#include <entities/IPlayerDefinition.hpp>
#include <engine/model/IRenderModel.hpp>

namespace CubA4
{
	class ICore;
}

namespace CubA4::mod
{
	class ModControl;
}

namespace CubA4::physics
{
	class IPhysicsEntityDefinition;
}

namespace CubA4::object
{
	class PlayerDefinition : public virtual IPlayerDefinition
	{
		using ModelType = CubA4::render::engine::model::IRenderModel;
	public:
		PlayerDefinition(std::shared_ptr<const CubA4::ICore> core, std::shared_ptr<const ModelType> model,
			std::shared_ptr<CubA4::physics::IPhysicsEntityDefinition> physicsDef,
			std::shared_ptr<const CubA4::mod::ModControl> modControl);
		~PlayerDefinition();

		IdType getId() const override;
		std::wstring getName() const override;

		void onComponentStage(IEntityFactoryBuilder &builder) const override;
		void onRenderPrepareStage(IEntityRenderBuilder &builder) const override;
	private:
		std::shared_ptr<const CubA4::ICore> core_;
		std::shared_ptr<const ModelType> model_;
		std::shared_ptr<CubA4::physics::IPhysicsEntityDefinition> physicsDef_;
		const std::shared_ptr<const CubA4::mod::ModControl> modControl_;
	};
}