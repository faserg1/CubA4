#include "../../include/world/World.hpp"
#include <world/IWorldDefinition.hpp>
#include <world/IWorldSubscriber.hpp>
#include <algorithm>
using namespace CubA4::world;
using namespace CubA4::mod::world;

World::World(std::shared_ptr<const IWorldDefinition> definition) :
	definition_(definition)
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

void World::subscribe(IWorldSubscriber *subscriber)
{
	subscribers_.push_back(subscriber);
}

void World::unsubscribe(IWorldSubscriber *subscriber)
{
	std::remove(subscribers_.begin(), subscribers_.end(), subscriber);
}

std::shared_ptr<const IWorldDefinition> World::getWorldDefinition() const
{
	return definition_;
}