#include "World.hpp"
#include "Chunk.hpp"
#include <world/IWorldDefinition.hpp>
#include <world/IWorldSubscriber.hpp>
#include <algorithm>

// test
#include <world/ChunkAssembler.hpp>

using namespace CubA4::world;

World::World(Core &core, std::shared_ptr<const IWorldDefinition> definition) :
	core_(core), definition_(definition)
{
	
}

World::~World()
{
	
}

std::string World::getId() const
{
	return definition_->getId();
}

std::wstring World::getName() const
{
	return definition_->getName();
}

std::unique_ptr<CubA4::util::ISubscription> World::subscribe(IWorldSubscriber *subscriber) const
{
	return std::move(subscriptionHelper_.add(subscriber));
}

std::shared_ptr<const IWorldDefinition> World::getWorldDefinition() const
{
	return definition_;
}

void World::addDimension(std::shared_ptr<Dimension> dim)
{
	dimensions_.insert(std::make_pair(dim->getId(), dim));
}

std::vector<std::shared_ptr<const IDimension>> World::getDimensions() const
{
	std::vector<std::shared_ptr<const IDimension>> result(dimensions_.size());
	std::transform(dimensions_.begin(), dimensions_.end(), result.begin(), [](auto pair) -> std::shared_ptr<const IDimension>
	{
		return pair.second;
	});
	return std::move(result);
}

std::shared_ptr<const IDimension> World::findDimension(std::string id) const
{
	auto it = dimensions_.find(id);
	if (it == dimensions_.end())
		return {};
	return it->second;
}

std::shared_ptr<Dimension> World::findDimension(std::string id)
{
	auto it = dimensions_.find(id);
	if (it == dimensions_.end())
		return {};
	return it->second;
}
