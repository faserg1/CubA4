#include <game/controller/Bindings.hpp>
#include <nlohmann/json.hpp>
#include <algorithm>
using namespace CubA4::game::controller;

Bindings::Bindings() = default;

Bindings::~Bindings() = default;

void Bindings::addKeyBinding(const std::string &action, Button btn, BMods mods)
{
	if (auto it = keyMap_.find(std::make_pair(btn, mods)); it != keyMap_.end())
	{
		if (std::find(it->second.begin(), it->second.end(), action) == it->second.end())
			it->second.push_back(action);
	}
	else
		keyMap_.insert(std::make_pair(std::make_pair(btn, mods), std::vector{action}));
	addKeyInBackwardsMap(action, btn, mods);
}

void Bindings::addAxisBinding(const std::string &action, AxisBinding axis)
{
	if (auto it = axisMap_.find(static_cast<uint32_t>(axis)); it != axisMap_.end())
	{
		if (std::find(it->second.begin(), it->second.end(), action) == it->second.end())
			it->second.push_back(action);
	}
	else
		axisMap_.insert(std::make_pair(static_cast<uint32_t>(axis), std::vector{action}));
}

void Bindings::removeKeyBinding(const std::string &action, Button btn, BMods mods)
{
	if (auto it = keyMap_.find(std::make_pair(btn, mods)); it != keyMap_.end())
	{
		auto toRemove = std::remove(it->second.begin(), it->second.end(), action);
		it->second.erase(toRemove, it->second.end());
	}
	removeKeyInBackwardsMap(action, btn, mods);
}

void Bindings::removeAxisBinding(const std::string &action, AxisBinding axis)
{
	if (auto it = axisMap_.find(static_cast<uint32_t>(axis)); it != axisMap_.end())
	{
		auto toRemove = std::remove(it->second.begin(), it->second.end(), action);
		it->second.erase(toRemove, it->second.end());
	}
}

const std::vector<std::string> *Bindings::getKeyAction(Button btn, BMods mods) const
{
	if (auto it = keyMap_.find(std::make_pair(btn, mods)); it != keyMap_.end())
		return &it->second;
	return nullptr;
}

const std::vector<std::string> *Bindings::getAxisAction(AxisBinding axis) const
{
	if (auto it = axisMap_.find(static_cast<uint32_t>(axis)); it != axisMap_.end())
		return &it->second;
	return nullptr;
}

bool Bindings::forEachKeyAction(const std::string &action, std::function<bool(Button, BMods)> callback) const
{
	const auto actionKeys = backKeyMap_.equal_range(action);
	for (auto it = actionKeys.first; it != actionKeys.second; it++)
	{
		auto [btn, bmods] = it->second;
		if (callback(btn, bmods))
			return true;
	}
	return false;
}

void Bindings::load(std::shared_ptr<const CubA4::resources::IResource> resource)
{
	auto data = resource->data();
	std::string_view s(static_cast<char*>(data.first.get()), data.second);
	auto j = nlohmann::json::parse(s);
	if (j.contains("keys"))
	{
		decltype(keyMap_) tempMap;
		j.at("keys").get_to(tempMap);
		for (auto binding : tempMap)
		{
			keyMap_.insert_or_assign(binding.first, binding.second);
			for (auto action : binding.second)
			{
				auto [btn, mods] = binding.first;
				addKeyInBackwardsMap(action, btn, mods);
			}
		}
	}
	if (j.contains("axis"))
	{
		decltype(axisMap_) tempMap;
		j.at("axis").get_to(tempMap);
		for (auto binding : tempMap)
			axisMap_.insert_or_assign(binding.first, binding.second);
	}
}

void Bindings::save(std::shared_ptr<CubA4::resources::IResource> resource) const
{
	nlohmann::json j {
		{"keys", keyMap_},
		{"axis", axisMap_}
	};
	auto s = j.dump(1, '\t', true);
	resource->save(s.data(), s.size());
}


void Bindings::addKeyInBackwardsMap(const std::string &action, Button btn, BMods mods)
{
	// TODO: Cheack of same exists
	backKeyMap_.insert(std::make_pair(action, std::make_pair(btn, mods)));
}

void Bindings::removeKeyInBackwardsMap(const std::string &action, Button btn, BMods mods)
{
	// TODO:
}