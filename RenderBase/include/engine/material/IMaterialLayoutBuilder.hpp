#ifndef RENDERBASE_IMATERIALLAYOUTBUILDER_HPP
#define RENDERBASE_IMATERIALLAYOUTBUILDER_HPP

#include <memory>

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace material
			{
				enum class MaterialType
				{
					Default, ///< Тип материала по умолчанию
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
		}
	}
}

#endif // RENDERBASE_IMATERIALLAYOUTBUILDER_HPP
