#pragma once

namespace CubA4::render::engine::material
{
	/**
	\brief Материал.
	\description Можно сказать, применяет текстуры и т.д.
	**/
	class IMaterial
	{
	public:

	protected:
		explicit IMaterial() = default;
		virtual ~IMaterial() = default;
	private:
	};
}
