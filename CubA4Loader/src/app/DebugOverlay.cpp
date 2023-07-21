#include "DebugOverlay.hpp"

#include <engine/IRenderEngine.hpp>
#include <engine/IRenderManager.hpp>
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
}