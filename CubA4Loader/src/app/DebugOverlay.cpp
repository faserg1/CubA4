#include "DebugOverlay.hpp"

#include <engine/IRenderEngine.hpp>
#include <engine/IRenderManager.hpp>
#include <engine/debug/IRenderDebug.hpp>
#include <engine/debug/IRenderDebugCollection.hpp>
#include <ui/IRenderUIManager.hpp>
#include <ui/IComponentFactory.hpp>
#include <ui/components/IText.hpp>

#include <fmt/format.h>

using namespace CubA4::app;
using namespace CubA4::render;
using namespace CubA4::render::engine;
using namespace CubA4::render::ui;

DebugOverlay::DebugOverlay(std::shared_ptr<IRenderEngine> renderEngine) :
	renderEngine_(renderEngine), renderUiManager_(renderEngine->getRenderManager()->getUIManager())
{
	auto uiManager = renderUiManager_.lock();
	auto factory = uiManager->getComponentFactory();
	

	debugOverlay_ = factory->createFrame();
	fpsLabel_ = factory->createText();
	fpsLabel_->setTextOffset(0, 32);

	debugOverlay_->addComponent(fpsLabel_);
	uiManager->getMainCanvas()->addComponent(debugOverlay_);

	auto debug = renderEngine->getRenderManager()->getDebug();
	auto col = debug->addCollection();
	col->addLine({0, 0, 0}, {0.f, 0.f, 0.f}, {20.f, 0.f, 0.f}, {1, 0, 0});
	col->addLine({0, 0, 0}, {0.f, 0.f, 0.f}, {0.f, 20.f, 0.f}, {0, 1, 0});
	col->addLine({0, 0, 0}, {0.f, 0.f, 0.f}, {0.f, 0.f, 20.f}, {0, 0, 1});
	worldLines_.push_back(col);
}

void DebugOverlay::update()
{
	if (auto renderEngine = renderEngine_.lock())
	{
		auto fps = renderEngine->getCurrentFPS();
		auto label = fmt::format("{:03}", fps);
		fpsLabel_->setText(label);
	}
}

void DebugOverlay::toggleVisibility()
{
	debugOverlay_->toggleVisibility();
	if (auto re = renderEngine_.lock())
	{
		re->getRenderManager()->getDebug()->toggleEnabled();
	}
}