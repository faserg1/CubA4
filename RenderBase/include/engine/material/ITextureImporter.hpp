#ifndef RENDERBASE_ITEXTUREIMPORTER_HPP
#define RENDERBASE_ITEXTUREIMPORTER_HPP

#include <memory>

namespace CubA4
{
	namespace core
	{
		namespace filesystem
		{
			class IAbstractResource;
		}
	}

	namespace render
	{
		namespace engine
		{
			namespace material
			{
				class ITexture;

				class ITextureImporter
				{
				public:
					virtual std::shared_ptr<ITexture> importFromPng(std::shared_ptr<const CubA4::core::filesystem::IAbstractResource> resource) const = 0;
					virtual std::shared_ptr<ITexture> importFromPng(void *ptr, size_t size) const = 0;
				protected:
					explicit ITextureImporter() = default;
					virtual ~ITextureImporter() = default;
				private:
				};
			}
		}
	}
}

#endif // RENDERBASE_ITEXTUREIMPORTER_HPP
