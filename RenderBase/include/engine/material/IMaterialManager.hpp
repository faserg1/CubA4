#pragma once

#include <memory>
#include <engine/material/IShaderFactory.hpp>
#include <engine/material/IMaterialLayoutSetFactory.hpp>
#include <engine/material/IMaterialFactory.hpp>
#include <engine/material/ITextureImporter.hpp>

namespace CubA4::render::engine::material
{
	class IMaterialManager
	{
	public:
		virtual std::shared_ptr<IShaderFactory> getShaderFactory() const = 0;
		virtual std::shared_ptr<IMaterialLayoutSetFactory> getMaterialLayoutSetFactory() const = 0;
		virtual std::shared_ptr<IMaterialFactory> getMaterialFactory() const = 0;
		virtual std::shared_ptr<ITextureImporter> getTextureImporter() const = 0;
	protected:
		explicit IMaterialManager() = default;
		virtual ~IMaterialManager() = default;
	private:
	};
}
