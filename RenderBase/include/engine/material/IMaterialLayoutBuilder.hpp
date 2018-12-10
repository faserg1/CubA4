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
				class IShader;

				///Строитель описания материала
				class IMaterialLayoutBuilder
				{
				public:
					virtual void useShader(std::shared_ptr<const IShader> shader) = 0;
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

#endif // RENDERBASE_IMATERIALLAYOUTBUILDER_HPP
