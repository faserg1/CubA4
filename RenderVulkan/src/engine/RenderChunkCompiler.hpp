#ifndef RENDERCHUNKCOMPILER_HPP
#define RENDERCHUNKCOMPILER_HPP

#include <memory>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Device;
		}

		namespace engine
		{
			class RenderChunkCompiler
			{
			public:
				explicit RenderChunkCompiler(std::shared_ptr<const vulkan::Device> device);
				~RenderChunkCompiler();
			protected:
			private:
				const std::shared_ptr<const vulkan::Device> device_;
			};
		}
	}
}

#endif // RENDERCHUNKCOMPILER_HPP
