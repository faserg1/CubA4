#include "./MaterialFactory.hpp"
#include "./MaterialBuilder.hpp"
using namespace CubA4::render::engine::material;

MaterialFactory::MaterialFactory()
{
	
}

MaterialFactory::~MaterialFactory()
{
	
}

std::shared_ptr<IMaterialBuilder> MaterialFactory::createMaterial(std::shared_ptr<const IMaterialLayout> layout)
{
	return std::make_shared<MaterialBuilder>(layout);
}