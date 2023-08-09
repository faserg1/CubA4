#include <entities/PlayerDefinition.hpp>
#include <object/IEntityRenderBuilder.hpp>
using namespace CubA4::object;

PlayerDefinition::PlayerDefinition(std::shared_ptr<const ModelType> model) :
	model_(model)
{

}

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

}

void PlayerDefinition::onRenderPrepareStage(IEntityRenderBuilder &builder) const
{
	builder.addModel(model_);
}