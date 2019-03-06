#include "./MaterialManager.hpp"
#include "./ShaderFactory.hpp"
#include "./MaterialLayoutSetFactory.hpp"
#include "./MaterialFactory.hpp"
#include "./TextureImporter.hpp"
using namespace CubA4::render::engine;
using namespace CubA4::render::engine::material;
using namespace CubA4::render::vulkan;

MaterialManager::MaterialManager(std::shared_ptr<const Device> device,
	std::shared_ptr<const Render> render,
	std::shared_ptr<ResourceManager> resourceManager) :
	device_(device), render_(render), resourceManager_(resourceManager)
{
	shaderFactory_ = std::make_shared<ShaderFactory>(device);
	materialFactory_ = std::make_shared<MaterialFactory>(device);
	textureImporter_ = std::make_shared<TextureImporter>(device);
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
	return std::make_shared<MaterialLayoutSetFactory>(device_, render_, resourceManager_);
}

std::shared_ptr<IMaterialFactory> MaterialManager::getMaterialFactory() const
{
	return materialFactory_;
}

std::shared_ptr<ITextureImporter> MaterialManager::getTextureImporter() const
{
	return textureImporter_;
}