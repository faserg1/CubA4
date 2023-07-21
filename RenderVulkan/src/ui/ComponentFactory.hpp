#pragma once

#include <ui/IComponentFactory.hpp>
#include <ui/UISkContext.hpp>

namespace CubA4::render::ui
{
	class ComponentFactory : public virtual IComponentFactory
	{
	public:
		ComponentFactory(std::shared_ptr<const UISkContext> context);

		std::shared_ptr<IImage> createImage(std::shared_ptr<const ITexture> texture) override;
		std::shared_ptr<IText> createText() override;
		std::shared_ptr<IFrame> createFrame() override;
	private:
		const std::shared_ptr<const UISkContext> context_;
	};
}