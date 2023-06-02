#pragma once

#include <memory>
#include <ui/IImage.hpp>
#include <ui/IFrame.hpp>
#include <engine/material/ITexture.hpp>

namespace CubA4::render::ui
{
	class IComponentFactory
	{
	protected:
		using ITexture = CubA4::render::engine::material::ITexture;
    public:
		virtual std::shared_ptr<IImage> createImage(std::shared_ptr<const ITexture> texture) = 0;
	};
}