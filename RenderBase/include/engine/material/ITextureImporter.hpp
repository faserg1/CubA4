#pragma once

#include <memory>

namespace CubA4
{
	namespace core
	{
		namespace resources
		{
			class IResource;
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
					virtual std::shared_ptr<ITexture> importFromPng(std::shared_ptr<const CubA4::core::resources::IResource> resource) const = 0;
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

