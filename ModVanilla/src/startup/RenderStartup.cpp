#include "./RenderStartup.hpp"
#include <ICore.hpp>
#include <logging/ILogger.hpp>
#include <logging/ILoggerTagged.hpp>
#include <resources/IResourcesManager.hpp>
#include <resources/IResource.hpp>
#include <system/IEnvironmentBuilder.hpp>
#include <IRenderInfo.hpp>
#include <engine/IRenderManager.hpp>
#include <engine/material/IMaterialManager.hpp>
#include <engine/material/IShaderFactory.hpp>
#include <engine/material/IMaterialLayoutBuilder.hpp>
#include <engine/material/IMaterialLayoutSetFactory.hpp>
#include <engine/material/IMaterialFactory.hpp>
#include <engine/material/IMaterialBuilder.hpp>
#include <engine/material/ITextureImporter.hpp>
#include <engine/model/IModelManager.hpp>
#include <model/IModelReader.hpp>
#include <manager/ModManager.hpp>
#include <ModVanillaConst.hpp>
#include "../../gen/irs.hpp"
#include <stdexcept>


using namespace CubA4::startup;
using namespace CubA4::logging;
using namespace CubA4::resources;
using namespace CubA4::manager;

RenderStartup::RenderStartup()
{

	
}

RenderStartup::~RenderStartup()
{
	
}

void RenderStartup::load(std::shared_ptr<const CubA4::ICore> core, std::shared_ptr<ModManager> manager)
{
	core_ = core;
	manager_ = manager;
	log_ = core_->getLogger()->createTaggedLog(LogSourceSystem::Mod, "ModVanilla/RenderStartup");
}

void RenderStartup::preinit(std::shared_ptr<CubA4::system::IEnvironmentBuilder> builder)
{
	auto &renderInfo = builder->getRenderInfo();
	if (renderInfo.getRenderEngineId() != "vulkan")
	{
		log_->log(LogLevel::Error, "Unsupported Render Engine: " + renderInfo.getRenderEngineId());
		throw std::runtime_error("Unsopported render engine");
	}
	auto renderManager = builder->getRenderManager();
	auto materialManager = renderManager->getMaterialManager();
	loadShaders(materialManager->getShaderFactory());
	createMaterialLayouts(materialManager->getMaterialLayoutSetFactory());
	importTextures(materialManager->getTextureImporter());
	createMaterials(materialManager->getMaterialFactory());
	createModels(renderManager->getModelManager());
}

void RenderStartup::loadShaders(std::shared_ptr<CubA4::render::engine::material::IShaderFactory> shaderFactory)
{
	// NOTE: [OOKAMI] Теперь в этом месте нужно будет грузить только шейдеры для пост-процессинга
}

void RenderStartup::createMaterialLayouts(std::shared_ptr<CubA4::render::engine::material::IMaterialLayoutSetFactory> layoutFactory)
{
	//auto renderManager = manager_->getModRenderManager();
	auto defaultLayoutBuilder = layoutFactory->createMaterialLayout();
	defaultLayoutBuilder->setType(CubA4::render::engine::material::MaterialType::Default);
	defaultLayoutBuilder->addTexture();
	auto layouts = layoutFactory->build();
	//renderManager->registerMaterialLayout(layouts[0], "default");
}

void RenderStartup::importTextures(std::shared_ptr<CubA4::render::engine::material::ITextureImporter> textureImporter)
{
	//auto renderManager = manager_->getModRenderManager();
	const auto resource = core_->getResourcesManager()->find("data/vanilla/assets/textures/NewTexture.png");
	auto importedTexture = textureImporter->importFromPng(resource);
	//renderManager->registerTexture(importedTexture, "newTexture");
}

void RenderStartup::createMaterials(std::shared_ptr<CubA4::render::engine::material::IMaterialFactory> materialFactory)
{
	//auto renderManager = manager_->getModRenderManager();
	//auto defaultMaterialBuilder = materialFactory->createMaterial(renderManager->getMaterialLayout("default"));
	//auto texture = renderManager->getTexture("newTexture");
	//defaultMaterialBuilder->addTexture(texture);
	//auto defaultMaterial = defaultMaterialBuilder->build();
	//renderManager->registerMaterial(defaultMaterial, "default");
}

void RenderStartup::createModels(std::shared_ptr<CubA4::render::engine::model::IModelManager> modelManager)
{
	//auto renderManager = manager_->getModRenderManager();
	auto modelFactory = core_->getModelFactory();
	auto resources = core_->getResourcesManager();
	auto resource = resources->find("data/vanilla/assets/models/test.json");
	auto blockModelDef = modelFactory->createSimpleBlockRenderModelDefinition("block", resource);
	auto blockModel = modelManager->registerModel(*blockModelDef);
	//renderManager->registerRenderModel(blockModel);
}