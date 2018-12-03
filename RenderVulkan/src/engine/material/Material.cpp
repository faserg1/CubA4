#include "./Material.hpp"
using namespace CubA4::render::engine::material;

Material::Material(std::shared_ptr<const MaterialLayout> layout) :
	layout_(layout)
{
	
}

Material::~Material()
{
	
}

std::shared_ptr<const MaterialLayout> Material::getLayout() const
{
	return layout_;
}