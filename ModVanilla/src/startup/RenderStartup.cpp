#include "./RenderStartup.hpp"
#include <ICore.hpp>
#include <logging/ILogger.hpp>
#include <logging/ILoggerTagged.hpp>
#include <system/IEnvironmentBuilder.hpp>
#include <IRenderInfo.hpp>
#include <engine/IRenderManager.hpp>
#include <engine/material/IMaterialManager.hpp>
#include <engine/material/IShaderFactory.hpp>
#include <stdexcept>
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
}

void RenderStartup::loadShaders(std::shared_ptr<CubA4::render::engine::material::IShaderFactory> shaderFactory)
{
	//shaderFactory->createFromBinary()
}