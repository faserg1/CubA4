#pragma once

#include <memory>

namespace CubA4::render::engine::material
{
	class IMaterial;
	class ITexture;

	class IMaterialBuilder
	{
	public:
		virtual std::shared_ptr<const IMaterial> build() = 0;
		virtual void addTexture(std::shared_ptr<const ITexture> texture) = 0;
	protected:
		explicit IMaterialBuilder() = default;
		virtual ~IMaterialBuilder() = default;
	private:
	};
}
