#include <engine/debug/RenderDebugCollection.hpp>
using namespace CubA4::render::engine::debug;

RenderDebugCollection::RenderDebugCollection(vulkan::CommandPool &cmdPool,
	std::shared_ptr<vulkan::RenderPass> renderPass,
	std::shared_ptr<IRenderDebugInternal> internal) :
	cmdPool_(cmdPool), renderPass_(renderPass), internal_(internal)
{

}

RenderDebugCollection::~RenderDebugCollection() = default;

void RenderDebugCollection::addLine(CubA4::world::ChunkPos chPos, CubA4::world::BasePos<float> from, CubA4::world::BasePos<float> to)
{
	auto i = internal_.lock();
	if (!i)
		return;

	std::vector<CubA4::model::Vertex> vertices(2);
	vertices[0].x = from.x;
	vertices[0].y = from.y;
	vertices[0].z = from.z;

	vertices[1].x = to.x;
	vertices[1].y = to.y;
	vertices[1].z = to.z;

	DebugModel model;
	model.type = PipelineType::Line;
	model.renderModel = i->createBuffer(std::move(vertices));
	model.chunkPos = chPos;

	models_.push_back(model);

	i->onCommandsDirty();
	dirty_ = true;
}

void RenderDebugCollection::hide()
{
	visible_ = false;
}

void RenderDebugCollection::show()
{
	visible_ = true;
}

bool RenderDebugCollection::isVisible() const
{
	return visible_;
}

void RenderDebugCollection::toggleVisibility()
{
	visible_ = !visible_;
}

void RenderDebugCollection::record(VkCommandBuffer primaryBuffer, uint32_t subpass, VkExtent2D extent)
{
	auto internal = internal_.lock();
	if (!internal)
	{
		// TODO: LOG ERROR!!
		return;
	}

	if (!buffer_)
	{
		std::vector<decltype(oldBuffers_)::iterator> toRemove;
		for (auto it = oldBuffers_.begin(); it != oldBuffers_.end(); it++)
		{
			//Remove?
		}

		cmdPool_.allocate(1, &buffer_, VK_COMMAND_BUFFER_LEVEL_SECONDARY);
	}

	if (buffer_ && !dirty_)
	{
		vkCmdExecuteCommands(primaryBuffer, 1, &buffer_);
		return;
	}
	
	auto worldSet = internal->getWorldDescriptorSet();

	VkCommandBufferInheritanceInfo inheritanceInfo = {};
	inheritanceInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
	inheritanceInfo.renderPass = renderPass_->getRenderPass();
	inheritanceInfo.subpass = subpass;

	VkCommandBufferBeginInfo beginInfo = {};
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_RENDER_PASS_CONTINUE_BIT | VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
	beginInfo.pInheritanceInfo = &inheritanceInfo;

	VkRect2D scissor = {};
	scissor.extent = extent;

	VkViewport viewport = {};
	viewport.x = 0;
	viewport.y = 0;
	viewport.minDepth = 0;
	viewport.maxDepth = 1;
	viewport.width = static_cast<float>(scissor.extent.width);
	viewport.height = static_cast<float>(scissor.extent.height);

	vkBeginCommandBuffer(buffer_, &beginInfo);
	/////////////////////////////////////////////////

	vkCmdSetViewport(buffer_, 0, 1, &viewport);
	vkCmdSetScissor(buffer_, 0, 1, &scissor);

	for (const auto &model : models_)
	{
		auto pipeline = internal->getPipeline(model.type);
		if (!pipeline)
			continue;
	
		pipeline->bind(buffer_);

		constexpr const uint16_t descriptorSetCount = 1;
		VkDescriptorSet sets[descriptorSetCount] = { worldSet->get()};

		vkCmdPushConstants(buffer_, pipeline->getLayout(), VK_SHADER_STAGE_ALL, 0, sizeof(model.chunkPos), &model.chunkPos);
		vkCmdBindDescriptorSets(buffer_, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline->getLayout(), 0, descriptorSetCount, sets, 0, nullptr);

		auto vBuffer = model.renderModel.vertexBuffer->get();
		static const VkDeviceSize offset = 0;
		vkCmdBindVertexBuffers(buffer_, 0, 1, &vBuffer, &offset);

		vkCmdDraw(buffer_, model.renderModel.vertexCount, 1, 0, 0);
	}

	/////////////////////////////////////////////////
	vkEndCommandBuffer(buffer_);

	vkCmdExecuteCommands(primaryBuffer, 1, &buffer_);
	dirty_ = false;
}
