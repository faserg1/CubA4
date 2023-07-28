#pragma once

#include <memory>
#include <vector>
#include <vulkan/pipeline/Pipeline.hpp>
#include <vulkan/util/VulkanHandlerContainer.hpp>
#include <engine/memory/IMemoryPart.hpp>
#include <model/PrimitiveTypes.hpp>

namespace CubA4::render::engine::debug
{
	enum class PipelineType
	{
		Line,
		Wireframe
	};

	struct VertexColor
	{
		float x;
		float y;
		float z;

		float r;
		float g;
		float b;
	};

	struct DebugRenderModel
	{
		std::shared_ptr<const CubA4::render::engine::memory::IMemoryPart> memoryPart;
		CubA4::render::vulkan::sVkBuffer vertexBuffer;
		uint32_t vertexCount;
	};

	class IRenderDebugInternal
	{
	public:
		virtual ~IRenderDebugInternal() = default;

		virtual void onCommandsDirty() = 0;
		virtual std::shared_ptr<CubA4::render::vulkan::Pipeline> getPipeline(PipelineType type) const = 0;
		virtual DebugRenderModel createBuffer(std::vector<VertexColor> vertices) = 0;
		virtual CubA4::render::vulkan::sVkDescriptorSet getWorldDescriptorSet() = 0;
	protected:
		IRenderDebugInternal() = default;

	};
}