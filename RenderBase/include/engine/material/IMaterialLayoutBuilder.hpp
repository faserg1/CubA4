#pragma once

#include <memory>

namespace CubA4::render::engine::material
{
	enum class MaterialType
	{
		Default, ///< Тип материала по умолчанию
		Block,
	};

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
