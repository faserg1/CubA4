#pragma once

#include <memory>
#include <engine/material/MaterialType.hpp>

namespace CubA4::render::engine::material
{
	///Строитель описания материала
	class IMaterialLayoutBuilder
	{
	public:
		virtual void setType(MaterialType type) = 0;
		virtual void addTexture() = 0;
	protected:
		explicit IMaterialLayoutBuilder() = default;
		virtual ~IMaterialLayoutBuilder() = default;
	private:
	};
}
