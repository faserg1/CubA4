#pragma once

#include <memory>
#include <vulkan/Device.hpp>
#include <engine/material/IMaterialManager.hpp>

namespace CubA4::render:: engine
{
	class Render;
	class ResourceManager;
}

namespace CubA4::render::engine::material
{
	class ShaderFactory;
	class MaterialLayoutSetFactory;
	class MaterialFactory;
	class TextureImporter;

	class MaterialManager :
		public virtual IMaterialManager
	{
	public:
		explicit MaterialManager(std::shared_ptr<const vulkan::Device> device,
			std::shared_ptr<const Render> render,
			std::shared_ptr<ResourceManager> resourceManager);
		~MaterialManager();

		std::shared_ptr<IShaderFactory> getShaderFactory() const override;
		std::shared_ptr<IMaterialLayoutSetFactory> getMaterialLayoutSetFactory() const override;
		std::shared_ptr<IMaterialFactory> getMaterialFactory() const override;
		std::shared_ptr<ITextureImporter> getTextureImporter() const override;
	protected:
	private:
		const std::shared_ptr<const vulkan::Device> device_;
		const std::shared_ptr<const Render> render_;
		const std::shared_ptr<ResourceManager> resourceManager_;
		std::shared_ptr<ShaderFactory> shaderFactory_;
		std::shared_ptr<MaterialFactory> materialFactory_;
		std::shared_ptr<TextureImporter> textureImporter_;
	};
}