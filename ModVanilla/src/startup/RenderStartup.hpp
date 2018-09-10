#ifndef RENDERSTARTUP_HPP
#define RENDERSTARTUP_HPP

#include <memory>

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
				class IShaderFactory;
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
			private:
				void loadShaders(std::shared_ptr<CubA4::render::engine::material::IShaderFactory> shaderFactory);
			};
		}
	}
}

#endif // RENDERSTARTUP_HPP
