#include "IdentityMap.hpp"
using namespace CubA4::system;

IdentityMap::IdentityMap() :
	counter_(0)
{
	
}

IdentityMap::IdentityMap(IdentityMap &&other) :
	counter_(other.counter_), map_(std::move(other.map_))
{
	
}

IdentityMap::IdentityMap(const IdentityMap &&other) :
	counter_(other.counter_), map_(std::move(other.map_))
{
	
}

IdentityMap::~IdentityMap()
{
	clear();
}

void IdentityMap::clear()
{
	counter_ = 0;
	map_.clear();
}

int64_t IdentityMap::add(const std::string &tag, const std::string &id)
{
	auto lastId = get(tag, id);
	if (lastId >= 0)
		return -1;
	const auto genId = counter_++;
	map_.insert(bm_value(genId, makeId(tag, id)));
	return genId;
}

int64_t IdentityMap::get(const std::string &tag, const std::string &id) const
{
	return get(makeId(tag, id));
}

int64_t IdentityMap::get(const std::string &fullId) const
{
	auto pair = map_.right.find(fullId);
	if (pair == map_.right.end())
		return -1;
	return pair->second;
}

std::string IdentityMap::get(int64_t id) const
{
	auto pair = map_.left.find(id);
	if (pair == map_.left.end())
		return {};
	return pair->second;
}

bool IdentityMap::parseId(const std::string &input, std::string &tag, std::string &id)
{
	// TODO: [OOKAMI] Распарсить идентификатор
	return false;
}

std::string IdentityMap::makeId(const std::string &tag, const std::string &id)
{
	return "#" + tag + "@" + id;
}