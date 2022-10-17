#include "./ModelFactory.hpp"
#include "./ModelReader.hpp"
#include "./SimpleRenderModelDefinition.hpp"
using namespace CubA4::mod::model;
using namespace CubA4::core::model;

ModelFactory::ModelFactory()
{
	reader_ = std::make_shared<ModelReader>();
}

ModelFactory::~ModelFactory()
{
	
}

std::shared_ptr<IRenderModelDefinition> ModelFactory::createSimpleRenderModelDefinition(const std::string &id, std::shared_ptr<const resources::IResource> model) const
{
	auto modelData = reader_->readRenderModel(model);
	return std::make_shared<SimpleRenderModelDefinition>(id, modelData);
}