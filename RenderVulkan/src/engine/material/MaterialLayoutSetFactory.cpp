#include "./MaterialLayoutSetFactory.hpp"
using namespace CubA4::render::engine::material;

MaterialLayoutSetFactory::MaterialLayoutSetFactory()
{
	
}

MaterialLayoutSetFactory::~MaterialLayoutSetFactory()
{
	
}

std::shared_ptr<IMaterialLayoutBuilder> MaterialLayoutSetFactory::createMaterialLayout()
{
	return {};
}

std::vector<std::shared_ptr<IMaterialLayout>> MaterialLayoutSetFactory::build()
{
	return {};
}