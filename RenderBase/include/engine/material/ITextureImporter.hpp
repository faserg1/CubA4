#pragma once

#include <memory>
#include <resources/IResource.hpp>

namespace CubA4::render::engine::material
{
	class ITexture;

	class ITextureImporter
	{
	public:
		virtual std::shared_ptr<ITexture> importFromPng(std::shared_ptr<const CubA4::resources::IResource> resource) const = 0;
		virtual std::shared_ptr<ITexture> importFromPng(void *ptr, size_t size) const = 0;
	protected:
		explicit ITextureImporter() = default;
		virtual ~ITextureImporter() = default;
	private:
	};
}
