#pragma once


#include <ui/components/IFrame.hpp>
#include <ui/components/BaseComponent.hpp>
#include <ui/expressions/Context.hpp>
#include <vector>

namespace CubA4::render::ui
{
	class Frame : public BaseComponent, public virtual IFrame
	{
	public:
		void addComponent(std::shared_ptr<IRenderUIBaseComponent> component) override;

		void draw(SkCanvas *parentCanvas) override;
		void updateContext(const Context &ctx) override;
	private:
		std::vector<std::shared_ptr<BaseComponent>> components_;
		Context ctx_;
	};
}