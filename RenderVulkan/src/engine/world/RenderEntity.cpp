#include <engine/world/RenderEntity.hpp>
using namespace CubA4::render::engine::world;

RenderEntity::RenderEntity(Data data, std::function<void()> deleter) :
	data_(data), deleter_(deleter)
{

}

RenderEntity::~RenderEntity()
{
	if (deleter_)
		deleter_();
}

bool RenderEntity::exists(IdFactoryType factoryId, IdEntityType entityId) const
{
	return data_.transforms_.find(std::make_pair(factoryId, entityId)) != data_.transforms_.end();
}

size_t RenderEntity::instanceCount() const
{
	return data_.transforms_.size();
}

void RenderEntity::executeFrom(VkCommandBuffer primaryCmdBuffer) const
{
	vkCmdExecuteCommands(primaryCmdBuffer, 1, &data_.cmdBuffer);
}

const RenderEntity::Data &RenderEntity::getData() const
{
	return data_;
}

RenderEntity::Data &RenderEntity::getData()
{
	return data_;
}