#include "./ModelFactory.hpp"
#include "./ModelReader.hpp"
#include <model/SimpleBlockRenderModelDefinition.hpp>
#include <model/SimpleRenderModelDefinition.hpp>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/filter.hpp>
using namespace CubA4::model;
using namespace CubA4::model;

ModelFactory::ModelFactory()
{
	reader_ = std::make_shared<ModelReader>();
}

ModelFactory::~ModelFactory()
{
	
}

std::shared_ptr<IBlockRenderModelDefinition> ModelFactory::createSimpleBlockRenderModelDefinition(const std::string &id, std::shared_ptr<const resources::IResource> model, RMaterialsMap map) const
{
	auto modelData = reader_->readBlockRenderModel(model);
	auto pred = [&](const std::pair<std::string, IBlockRenderModelDefinition::RMaterial> &pair) { return modelData.materials.find(pair.first) != modelData.materials.end(); };
	auto usedMap = map | ranges::views::filter(pred) | ranges::to<std::unordered_map>;
	return std::make_shared<SimpleBlockRenderModelDefinition>(id, modelData, usedMap);
}

std::shared_ptr<IRenderModelDefinition> ModelFactory::createSimpleRenderModelDefinition(const std::string &id, std::shared_ptr<const resources::IResource> model, RMaterialsMap map) const
{
	auto modelData = reader_->readRenderModel(model);
	auto pred = [&](const std::pair<std::string, IRenderModelDefinition::RMaterial> &pair) { return modelData.materials.find(pair.first) != modelData.materials.end(); };
	auto usedMap = map | ranges::views::filter(pred) | ranges::to<std::unordered_map>;
	return std::make_shared<SimpleRenderModelDefinition>(id, modelData, usedMap);
}