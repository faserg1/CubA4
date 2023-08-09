#include <engine/model/EntityRenderModel.hpp>
using namespace CubA4::render::engine::model;

EntityRenderModel::EntityRenderModel(std::shared_ptr<const vulkan::Device> device, RenderModelData data, std::shared_ptr<const IMaterial> material) :
	RenderModel(device, data), material_(std::dynamic_pointer_cast<const Material>(material))
{

}

EntityRenderModel::~EntityRenderModel()
{

}

std::shared_ptr<const EntityRenderModel::Material> EntityRenderModel::getMaterial() const
{
	return material_;
}