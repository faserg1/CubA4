#include "./MaterialManager.hpp"
#include "./ShaderFactory.hpp"
#include "./MaterialLayoutSetFactory.hpp"
using namespace CubA4::render::engine::material;
using namespace CubA4::render::vulkan;

MaterialManager::MaterialManager(std::shared_ptr<const Device> device) :
	device_(device)
{
	shaderFactory_ = std::make_shared<ShaderFactory>(device);
	materialLayoutSetFactory_ = std::make_shared<MaterialLayoutSetFactory>(device);
}

MaterialManager::~MaterialManager()
{
	
}

std::shared_ptr<IShaderFactory> MaterialManager::getShaderFactory() const
{
	return shaderFactory_;
}

std::shared_ptr<IMaterialLayoutSetFactory> MaterialManager::getMaterialLayoutSetFactory() const
{
	return materialLayoutSetFactory_;
}