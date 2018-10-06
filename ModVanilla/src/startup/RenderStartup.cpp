#include "./RenderStartup.hpp"
#include <ICore.hpp>
#include <logging/ILogger.hpp>
#include <logging/ILoggerTagged.hpp>
#include <system/IEnvironmentBuilder.hpp>
#include <IRenderInfo.hpp>
#include <engine/IRenderManager.hpp>
#include <engine/material/IMaterialManager.hpp>
#include <engine/material/IShaderFactory.hpp>
#include <engine/material/IMaterialLayoutBuilder.hpp>
#include <engine/material/IMaterialLayoutSetFactory.hpp>
#include <engine/model/IModelManager.hpp>
#include "../../gen/irs.hpp"
#include <stdexcept>

#include "../render/BlockModel.hpp"
using namespace CubA4::mod::startup;
using namespace CubA4::core::logging;

RenderStartup::RenderStartup()
{

	
}

RenderStartup::~RenderStartup()
{
	
}

void RenderStartup::load(std::shared_ptr<const CubA4::core::ICore> core)
{
	core_ = core;
	log_ = std::shared_ptr<ILoggerTagged>(core_->getLogger()->createTaggedLog(LogSourceSystem::Mod, "ModVanilla/RenderStartup"));
}

void RenderStartup::init(std::shared_ptr<CubA4::core::system::IEnvironmentBuilder> builder)
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
	createModels(renderManager->getModelManager());
}

void RenderStartup::loadShaders(std::shared_ptr<CubA4::render::engine::material::IShaderFactory> shaderFactory)
{
	size_t shaderSize;
	const void *data = irs::findFile("compiled/default.frag.spv", shaderSize);
	auto fragShader = shaderFactory->createFromBinary(data, shaderSize, CubA4::render::engine::material::ShaderType::Fragment, "main");
	shaders_.insert(std::make_pair("default.frag", fragShader));
	data = irs::findFile("compiled/default.vert.spv", shaderSize);
	auto vertexShader = shaderFactory->createFromBinary(data, shaderSize, CubA4::render::engine::material::ShaderType::Vertex, "main");
	shaders_.insert(std::make_pair("default.vert", vertexShader));
}

void RenderStartup::createMaterialLayouts(std::shared_ptr<CubA4::render::engine::material::IMaterialLayoutSetFactory> layoutFactory)
{
	auto defaultLayoutBuilder = layoutFactory->createMaterialLayout();
	defaultLayoutBuilder->useShader(shaders_.find("default.frag")->second);
	defaultLayoutBuilder->useShader(shaders_.find("default.vert")->second);
	auto layouts = layoutFactory->build();
}

void RenderStartup::createModels(std::shared_ptr<CubA4::render::engine::model::IModelManager> modelManager)
{
	auto blockModelDef = render::BlockModel();
	auto blockModel = modelManager->registerModel(blockModelDef);
}