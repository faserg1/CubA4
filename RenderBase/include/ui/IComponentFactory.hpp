#pragma once

#include <memory>
#include <ui/components/IImage.hpp>
#include <ui/components/IFrame.hpp>
#include <ui/components/IText.hpp>
#include <engine/material/ITexture.hpp>

namespace CubA4::render::ui
{
	class IComponentFactory
	{
	protected:
		using ITexture = CubA4::render::engine::material::ITexture;
    public:
		virtual std::shared_ptr<IImage> createImage(std::shared_ptr<const ITexture> texture) = 0;
		virtual std::shared_ptr<IText> createText() = 0;
		virtual std::shared_ptr<IFrame> createFrame() = 0;
	};
}