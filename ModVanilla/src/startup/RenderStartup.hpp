#ifndef RENDERSTARTUP_HPP
#define RENDERSTARTUP_HPP

#include <memory>
#include <string>
#include <map>

namespace CubA4
{
	namespace core
	{
		class ICore;

		namespace logging
		{
			class ILoggerTagged;
		}

		namespace system
		{
			class IEnvironmentBuilder;
		}
	}

	namespace render
	{
		namespace engine
		{
			namespace material
			{
				class IMaterialLayoutSetFactory;
				class IShaderFactory;
				class IShader;
			}
		}
	}

	namespace mod
	{
		namespace startup
		{
			class RenderStartup
			{
			public:
				explicit RenderStartup();
				~RenderStartup();

				void load(std::shared_ptr<const core::ICore> core);
				void init(std::shared_ptr<CubA4::core::system::IEnvironmentBuilder> builder);
			protected:
			private:
				std::shared_ptr<const CubA4::core::ICore> core_;
				std::shared_ptr<CubA4::core::logging::ILoggerTagged> log_;
				std::map<std::string, std::shared_ptr<CubA4::render::engine::material::IShader>> shaders_;
			private:
				void loadShaders(std::shared_ptr<CubA4::render::engine::material::IShaderFactory> shaderFactory);
				void createMaterialLayouts(std::shared_ptr<CubA4::render::engine::material::IMaterialLayoutSetFactory> layoutFactory);
				void createModels();
			};
		}
	}
}

#endif // RENDERSTARTUP_HPP
