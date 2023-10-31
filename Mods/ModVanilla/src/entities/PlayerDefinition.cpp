#include <entities/PlayerDefinition.hpp>
#include <object/IEntityRenderBuilder.hpp>
#include <object/IEntityFactoryBuilder.hpp>
#include <physics/IPhysicsEntityDefinition.hpp>
#include <controller/PlayerController.hpp>
using namespace CubA4::object;

PlayerDefinition::PlayerDefinition(std::shared_ptr<const CubA4::ICore> core, std::shared_ptr<const ModelType> model,
	std::shared_ptr<CubA4::physics::IPhysicsEntityDefinition> physicsDef,
	std::shared_ptr<const CubA4::mod::ModControl> modControl) :
	core_(core), model_(model), physicsDef_(std::move(physicsDef)), modControl_(modControl)
{

}

PlayerDefinition::~PlayerDefinition() = default;

PlayerDefinition::IdType PlayerDefinition::getId() const
{
	return "player";
}

std::wstring PlayerDefinition::getName() const
{
	return L"Player";
}

void PlayerDefinition::onComponentStage(IEntityFactoryBuilder &builder) const
{
	if (physicsDef_)
		builder.applyPhysicsDefinition(*physicsDef_);

	builder
		.attachCamera()
		.attachController(nullptr, [this](CubA4::object::EntityContextActions &actions)
		{
			actions.addHandler(std::make_shared<PlayerController>(core_, modControl_));
		})
		;
}

void PlayerDefinition::onRenderPrepareStage(IEntityRenderBuilder &builder) const
{
	builder.addModel(model_);
}