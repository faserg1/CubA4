#pragma once

#include <memory>
#include <engine/material/IRenderTargetTexture.hpp>
#include <engine/pipeline/Stage.hpp>

namespace CubA4::render::engine::pipeline
{
	class IRenderTargetScene
	{
	public:
		virtual ~IRenderTargetScene() = default;

		std::shared_ptr<CubA4::render::engine::material::IRenderTargetTexture> getTargetTexture() = 0;
	protected:
		explicit IRenderTargetScene() = default;
	};
}
