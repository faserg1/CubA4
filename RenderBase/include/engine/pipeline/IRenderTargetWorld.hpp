#pragma once

namespace CubA4::render::engine::pipeline
{
	class IRenderTargetWorld
	{
	public:
		virtual ~IRenderTargetWorld() = default;
	protected:
		explicit IRenderTargetWorld() = default;
	};
}
