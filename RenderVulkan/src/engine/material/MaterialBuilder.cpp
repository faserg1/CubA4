#include "./MaterialBuilder.hpp"
#include "./MaterialLayout.hpp"
#include "./Material.hpp"
using namespace CubA4::render::engine::material;

MaterialBuilder::MaterialBuilder(std::shared_ptr<const IMaterialLayout> layout) :
	layout_(layout)
{
	
}

MaterialBuilder::~MaterialBuilder()
{
	
}

std::shared_ptr<const IMaterial> MaterialBuilder::build()
{
	return std::make_shared<Material>(std::dynamic_pointer_cast<const MaterialLayout>(layout_));
}