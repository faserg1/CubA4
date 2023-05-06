#pragma once

namespace CubA4::render::engine::pipeline
{
	class IRenderTargetSceneCamera
	{
	public:
		virtual ~IRenderTargetSceneCamera() = default;
	protected:
		explicit IRenderTargetSceneCamera() = default;
	};
}
