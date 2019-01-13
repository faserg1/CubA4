#ifndef RENDERVULKAN_TEXTUREIMPORTER_HPP
#define RENDERVULKAN_TEXTUREIMPORTER_HPP

#include <memory>

namespace CubA4
{
	namespace render
	{
		namespace engine
		{
			namespace material
			{
				class Texture;

				class TextureImporter
				{
				public:
					explicit TextureImporter();
					~TextureImporter();

					std::shared_ptr<Texture> importPng();
				protected:
				private:
				};
			}
		}
	}
}

#endif // RENDERVULKAN_TEXTUREIMPORTER_HPP
