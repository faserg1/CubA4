#include "./RenderStartup.hpp"
#include <ICore.hpp>
#include <logging/ILogger.hpp>
#include <logging/ILoggerTagged.hpp>
#include <resources/IResourcesManager.hpp>
#include <resources/IResource.hpp>
#include <core/IEnvironmentBuilder.hpp>
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
#include <ui/IRenderUIManager.hpp>
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

void RenderStartup::preinit(std::shared_ptr<CubA4::core::IEnvironmentBuilder> builder)
{
	auto &renderInfo = builder->getRenderInfo();
	/*if (renderInfo.getRenderEngineId() != "vulkan")
	{
		log_->log(LogLevel::Error, "Unsupported Render Engine: " + renderInfo.getRenderEngineId());
		throw std::runtime_error("Unsopported render engine");
	}*/
	renderManager_ = builder->getRenderManager();
	auto materialManager = renderManager_->getMaterialManager();
	loadShaders(materialManager->getShaderFactory());
	createMaterialLayouts(materialManager->getMaterialLayoutSetFactory());
	importTextures(materialManager->getTextureImporter());
	createMaterials(materialManager->getMaterialFactory());
	createModels(renderManager_->getModelManager());
	testUI();
}

std::shared_ptr<CubA4::render::engine::IRenderManager> RenderStartup::getRenderManager() const
{
	return renderManager_;
}

void RenderStartup::loadShaders(std::shared_ptr<CubA4::render::engine::material::IShaderFactory> shaderFactory)
{
	// NOTE: [OOKAMI] Теперь в этом месте нужно будет грузить только шейдеры для пост-процессинга
}

void RenderStartup::createMaterialLayouts(std::shared_ptr<CubA4::render::engine::material::IMaterialLayoutSetFactory> layoutFactory)
{
	auto defaultLayoutBuilder = layoutFactory->createMaterialLayout();
	defaultLayoutBuilder->setType(CubA4::render::engine::material::MaterialType::Block);
	defaultLayoutBuilder->addTexture();
	


	auto entityLayoutBuilder = layoutFactory->createMaterialLayout();
	entityLayoutBuilder->setType(CubA4::render::engine::material::MaterialType::Entity);
	entityLayoutBuilder->addTexture();

	auto layouts = layoutFactory->build();

	materialLayouts_.insert(std::make_pair("default", layouts[0]));
	materialLayouts_.insert(std::make_pair("entity", layouts[1]));
}

void RenderStartup::importTextures(std::shared_ptr<CubA4::render::engine::material::ITextureImporter> textureImporter)
{
	std::vector<std::string> textures = {
		"NewTexture",
		"01",
		"02",
		"03",
		"stone01",
		"grass00",
		"grass01",
		"grass02",
		"dirt00"
	};
	for (auto texName : textures)
	{
		using namespace std::string_literals;
		const auto resource = core_->getResourcesManager()->find("data/vanilla/assets/textures/"s + texName + ".png"s);
		auto importedTexture = textureImporter->importFromPng(resource);
		textures_.insert(std::make_pair(texName, importedTexture));
	}
}

void RenderStartup::createMaterials(std::shared_ptr<CubA4::render::engine::material::IMaterialFactory> materialFactory)
{
	auto texture = textures_.find("NewTexture")->second;
	
	auto layoutDefault = materialLayouts_.find("default")->second;
	auto layoutEntity = materialLayouts_.find("entity")->second;

	auto defaultMaterialBuilder = materialFactory->createMaterial(layoutDefault);
	defaultMaterialBuilder->addTexture(texture);
	auto defaultMaterial = defaultMaterialBuilder->build();
	materials_.insert(std::make_pair("default", defaultMaterial));

	auto entityMaterialBuilder = materialFactory->createMaterial(layoutEntity);
	entityMaterialBuilder->addTexture(texture);
	auto entityMaterial = entityMaterialBuilder->build();
	materials_.insert(std::make_pair("entity", entityMaterial));

	std::vector<std::string> textures = {
		"01",
		"02",
		"03",
		"stone01",
		"grass00",
		"grass01",
		"grass02",
		"dirt00"
	};
	for (auto texName : textures)
	{
		auto texture = textures_.find(texName)->second;
		auto materialBuilder = materialFactory->createMaterial(layoutDefault);
		materialBuilder->addTexture(texture);
		auto material = materialBuilder->build();
		materials_.insert(std::make_pair(texName, material));
	}
	core_->getLogger()->flush();
}

void RenderStartup::createModels(std::shared_ptr<CubA4::render::engine::model::IModelManager> modelManager)
{
	auto modelFactory = core_->getModelFactory();
	auto resources = core_->getResourcesManager();
	auto resource1 = resources->find("data/vanilla/assets/models/test.json");
	auto resource2 = resources->find("data/vanilla/assets/models/test2.json");
	auto resource3 = resources->find("data/vanilla/assets/models/test-cube-player.json");
	auto blockModelDef1 = modelFactory->createSimpleBlockRenderModelDefinition("block", resource1, materials_);
	auto blockModelDef2 = modelFactory->createSimpleBlockRenderModelDefinition("block2", resource2, materials_);
	auto entityModelDef1 = modelFactory->createSimpleRenderModelDefinition("player", resource3, materials_);
	
	auto blockManager = manager_->getBlockManager();
	blockManager->addBlockDefinition("test1", blockModelDef1);
	blockManager->addBlockDefinition("test2", blockModelDef2);

	auto modRenderManager = manager_->getRenderManager();
	auto model3 = modelManager->registerEntityModel(*entityModelDef1);
	modRenderManager->addModel("test-cube-player", model3);

	//auto blockModel = modelManager->registerModel(*blockModelDef);
}

void RenderStartup::testUI()
{
	auto materialManager = renderManager_->getMaterialManager();
	auto textureImporter = materialManager->getTextureImporter();
	auto uiManager = renderManager_->getUIManager();
	auto mainCanvas = uiManager->getMainCanvas();
	using namespace std::string_literals;
	using namespace CubA4::render::ui_literals;
	const auto resource = core_->getResourcesManager()->find("data/vanilla/assets/ui/button.png"s);
	auto importedTexture = textureImporter->importFromPng(resource);
	auto image = uiManager->getComponentFactory()->createImage(importedTexture);
	image->setImageNinePath({4, 4, 24, 24}, {10_px, 50_px, 50_vw + 10_px, 5_vh + 50_px});
	image->setMode(CubA4::render::ui::ImageMode::NinePath);
	mainCanvas->addComponent(image);
}