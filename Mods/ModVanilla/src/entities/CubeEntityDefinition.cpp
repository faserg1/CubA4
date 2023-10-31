#include <entities/CubeEntityDefinition.hpp>
#include <object/IEntityRenderBuilder.hpp>
#include <object/IEntityFactoryBuilder.hpp>
#include <physics/IPhysicsEntityDefinition.hpp>
using namespace CubA4::object;

CubeEntityDefinition::CubeEntityDefinition(std::shared_ptr<const CubA4::ICore> core, std::shared_ptr<const ModelType> model, std::shared_ptr<CubA4::physics::IPhysicsEntityDefinition> physicsDef) :
	core_(core), model_(model), physicsDef_(std::move(physicsDef))
{

}

CubeEntityDefinition::~CubeEntityDefinition() = default;

CubeEntityDefinition::IdType CubeEntityDefinition::getId() const
{
	return "cube";
}

std::wstring CubeEntityDefinition::getName() const
{
	return L"Cube";
}

void CubeEntityDefinition::onComponentStage(IEntityFactoryBuilder &builder) const
{
	if (physicsDef_)
		builder.applyPhysicsDefinition(*physicsDef_);
}

void CubeEntityDefinition::onRenderPrepareStage(IEntityRenderBuilder &builder) const
{
	builder.addModel(model_);
}