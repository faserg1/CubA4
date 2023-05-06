#pragma once

namespace CubA4::render::engine::pipeline
{
	class IRenderTargetWorldCamera
	{
	public:
		virtual ~IRenderTargetWorldCamera() = default;
	protected:
		explicit IRenderTargetWorldCamera() = default;
	};
}
