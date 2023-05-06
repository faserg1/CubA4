#pragma once

#include <engine/material/ITexture.hpp>

namespace CubA4::render::engine::material
{
	class IRenderTargetTexture : public virtual ITexture
	{
	public:
		virtual ~IRenderTargetTexture() = default;
	protected:
		explicit IRenderTargetTexture() = default;
	};
}
