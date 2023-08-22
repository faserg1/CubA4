#pragma once

#include <memory>
#include <string>
#include <map>

#include <ICore.hpp>
#include <manager/ModManager.hpp>
#include <core/IEnvironmentBuilder.hpp>
#include <logging/ILogger.hpp>
#include <logging/ILoggerTagged.hpp>
#include <model/IBlockRenderModelDefinition.hpp>

namespace CubA4::render::engine::material
{
	class IMaterialLayoutSetFactory;
	class IMaterialLayout;
	class IMaterial;
	class ITexture;
	class IMaterialFactory;
	class ITextureImporter;
	class IShaderFactory;
	class IShader;
}

namespace CubA4::render::engine::model
{
	class IModelManager;
}

namespace CubA4::startup
{
	class RenderStartup
	{
		using Texture = std::shared_ptr<const CubA4::render::engine::material::ITexture>;
		using Material = std::shared_ptr<const CubA4::render::engine::material::IMaterial>;
		using MaterialLayout = std::shared_ptr<const CubA4::render::engine::material::IMaterialLayout>;
	public:
		explicit RenderStartup();
		~RenderStartup();

		void load(std::shared_ptr<const ICore> core, std::shared_ptr<manager::ModManager> manager);
		void preinit(std::shared_ptr<CubA4::core::IEnvironmentBuilder> builder);
	protected:
	private:
		std::shared_ptr<const CubA4::ICore> core_;
		std::shared_ptr<manager::ModManager> manager_;
		std::shared_ptr<CubA4::logging::ILoggerTagged> log_;
		std::map<std::string, std::shared_ptr<const CubA4::render::engine::material::IShader>> shaders_;
	private:
		void loadShaders(std::shared_ptr<CubA4::render::engine::material::IShaderFactory> shaderFactory);
		void createMaterialLayouts(std::shared_ptr<CubA4::render::engine::material::IMaterialLayoutSetFactory> layoutFactory);
		void importTextures(std::shared_ptr<CubA4::render::engine::material::ITextureImporter> textureImporter);
		void createMaterials(std::shared_ptr<CubA4::render::engine::material::IMaterialFactory> materialFactory);
		void createModels(std::shared_ptr<CubA4::render::engine::model::IModelManager> modelManager);

		// test!!!!!!
		void testUI(std::shared_ptr<CubA4::render::engine::IRenderManager> renderManager);
	private:
		std::map<std::string, Texture> textures_;
		std::map<std::string, Material> materials_;
		std::map<std::string, MaterialLayout> materialLayouts_;
	};
}
