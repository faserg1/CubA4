#include <ui/components/Frame.hpp>
using namespace CubA4::render::ui;

void Frame::addComponent(std::shared_ptr<IRenderUIBaseComponent> component)
{
	auto baseComponent = std::dynamic_pointer_cast<BaseComponent>(component);
	baseComponent->updateContext(ctx_);
	components_.push_back(baseComponent);
}

void Frame::draw(SkCanvas *parentCanvas)
{
	if (!visibility_)
		return;
	for (auto component : components_)
	{
		parentCanvas->save();
		component->draw(parentCanvas);
		parentCanvas->restore();
	}
}

void Frame::updateContext(const Context &ctx)
{
	ctx_ = ctx;
	for (auto component : components_)
	{
		// TODO: take frame size?
		component->updateContext(ctx);
	}
}