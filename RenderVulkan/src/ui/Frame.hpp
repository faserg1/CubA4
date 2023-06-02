#pragma once


#include <ui/IFrame.hpp>
#include <ui/BaseComponent.hpp>
#include <vector>

namespace CubA4::render::ui
{
	class Frame : public BaseComponent, public virtual IFrame
	{
	public:
		void addComponent(std::shared_ptr<IRenderUIBaseComponent> component) override;

		void draw(SkCanvas *parentCanvas) override;
	private:
		std::vector<std::shared_ptr<BaseComponent>> components_;
	};
}