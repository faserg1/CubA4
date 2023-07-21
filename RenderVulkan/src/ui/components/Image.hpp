#pragma once

#include <memory>
#include <ui/components/IImage.hpp>
#include <ui/components/BaseComponent.hpp>
#include <engine/material/ITexture.hpp>
#include <skia/include/core/SkImage.h>

namespace CubA4::render::ui
{
	class Image : public BaseComponent, public virtual IImage
	{
		using ITexture = CubA4::render::engine::material::ITexture;
	public:
		Image(std::shared_ptr<const ITexture> texture, sk_sp<SkImage> image);

		void draw(SkCanvas *parentCanvas) override;
	private:
		std::shared_ptr<const ITexture> texture_;
		sk_sp<SkImage> image_;
	};
}