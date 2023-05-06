#pragma once

namespace CubA4::render::engine::material
{
	class ITexture
	{
	public:
		virtual ~ITexture() = default;
	protected:
		explicit ITexture() = default;
	private:
	};
}
