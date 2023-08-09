#include <object/EntityRenderBuilder.hpp>
#include <object/EntityBuilderData.hpp>
using namespace CubA4::object;

EntityRenderBuilder::EntityRenderBuilder(EntityBuilderData &data) :
	data_(data)
{

}

void EntityRenderBuilder::addModel(std::shared_ptr<const CubA4::render::engine::model::IRenderModel> model)
{
	data_.renderModel = model;
}