#include "../../include/system/IdentityMap.hpp"
using namespace CubA4::core::system;

IdentityMap::IdentityMap()
{
	
}

IdentityMap::~IdentityMap()
{
	
}

void IdentityMap::clear()
{
	map_.clear();
}

int64_t IdentityMap::add(const std::string &tag, const std::string &id)
{
	const auto genId = counter_++;
	map_.insert(bm_value(genId, makeId(tag, id)));
	return genId;
}

int64_t IdentityMap::get(const std::string &tag, const std::string &id) const
{
	return map_.right.find(makeId(tag, id))->second;
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