#ifndef RENDERCHUNKCOMPILER_HPP
#define RENDERCHUNKCOMPILER_HPP

#include <memory>
#include <vulkan/vulkan.h>
#include <vector>
#include <atomic>
#include <future>
#include <cstddef>
#include "RenderChunkCompilerCore.hpp"

namespace CubA4
{
	namespace mod
	{
		namespace world
		{
			class IChunk;
		}
	}


	namespace render
	{
		namespace vulkan
		{
			class RenderPass;
		}

		namespace engine
		{
			namespace world
			{
				class RenderChunk;
			}

			class RenderChunkCompiler :
				public RenderChunkCompilerCore
			{
			public:
				explicit RenderChunkCompiler(std::shared_ptr<const vulkan::Device> device, std::shared_ptr<const vulkan::RenderPass> renderPass);
				explicit RenderChunkCompiler(const RenderChunkCompiler &) = delete;
				~RenderChunkCompiler();

				std::shared_future<std::shared_ptr<const world::RenderChunk>> compileChunk(std::shared_ptr<CubA4::mod::world::IChunk> chunk);
			protected:
			private:
				std::shared_ptr<const world::RenderChunk> compileChunkInternal(std::shared_ptr<CubA4::mod::world::IChunk> chunk);
			private:
				std::shared_ptr<const vulkan::RenderPass> renderPass_;
			};
		}
	}
}

#endif // RENDERCHUNKCOMPILER_HPP
