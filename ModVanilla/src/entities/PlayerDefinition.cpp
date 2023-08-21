#include <entities/PlayerDefinition.hpp>
#include <object/IEntityRenderBuilder.hpp>
#include <object/IEntityFactoryBuilder.hpp>
#include <physics/IPhysicsEntityDefinition.hpp>
using namespace CubA4::object;

PlayerDefinition::PlayerDefinition(std::shared_ptr<const ModelType> model, std::shared_ptr<CubA4::physics::IPhysicsEntityDefinition> physicsDef) :
	model_(model), physicsDef_(std::move(physicsDef))
{

}

PlayerDefinition::~PlayerDefinition() = default;

PlayerDefinition::IdType PlayerDefinition::getId() const
{
	return "player";
}

std::wstring PlayerDefinition::getName() const
{
	return L"Игрок";
}

void PlayerDefinition::onComponentStage(IEntityFactoryBuilder &builder) const
{
	if (physicsDef_)
		builder.applyPhysicsDefinition(*physicsDef_);
}

void PlayerDefinition::onRenderPrepareStage(IEntityRenderBuilder &builder) const
{
	builder.addModel(model_);
}