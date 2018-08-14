#ifndef IMATERIALLAYOUTBUILDER_HPP
#define IMATERIALLAYOUTBUILDER_HPP

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace material
			{
				///Строитель описания материала
				class IMaterialLayoutBuilder
				{
				public:
					/// Устанавливает режим прозрачности материала. По умолчанию материал непрозрачен
					virtual void setTransparentMode(bool transparent = true) = 0;
					// useShader()
					// addSampler()
					// add..*
				protected:
					explicit IMaterialLayoutBuilder() = default;
					virtual ~IMaterialLayoutBuilder() = default;
				private:
				};
			}
		}
	}
}

#endif // IMATERIALLAYOUTBUILDER_HPP
