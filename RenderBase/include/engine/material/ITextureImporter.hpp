#ifndef RENDERBASE_ITEXTUREIMPORTER_HPP
#define RENDERBASE_ITEXTUREIMPORTER_HPP

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace material
			{
				class ITextureImporter
				{
				public:
					virtual ~ITextureImporter() = default;
				protected:
					explicit ITextureImporter() = default;
				private:
				};
			}
		}
	}
}

#endif // RENDERBASE_ITEXTUREIMPORTER_HPP
