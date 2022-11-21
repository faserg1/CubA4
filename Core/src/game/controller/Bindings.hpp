#pragma once

#include <game/controller/IBindings.hpp>
#include <unordered_map>
#include <memory>

template<>
struct std::hash<std::pair<CubA4::game::controller::Button, CubA4::game::controller::BMods>>
{
    std::size_t operator()(const std::pair<CubA4::game::controller::Button, CubA4::game::controller::BMods>& s) const noexcept
    {
        std::size_t h1 = std::hash<decltype(s.first)>{}(s.first);
        std::size_t h2 = std::hash<decltype(s.second)>{}(s.second);
        return h1 ^ (h2 << 1);
    }
};

namespace CubA4::game::controller
{
	class Bindings : public virtual IBindings
	{
	public:
		explicit Bindings();
		~Bindings();

		void addKeyBinding(const std::string &action, Button btn, BMods mods) override;
		void addAxisBinding(const std::string &action, AxisBinding axis) override;

		void removeKeyBinding(const std::string &action, Button btn, BMods mods) override;
		void removeAxisBinding(const std::string &action, AxisBinding axis) override;

		const std::vector<std::string> *getKeyAction(Button btn, BMods mods) const override;
		const std::vector<std::string> *getAxisAction(AxisBinding axis) const override;

		bool forEachKeyAction(const std::string &action, std::function<bool(Button, BMods)> callback) const override;

		void load(std::shared_ptr<const CubA4::resources::IResource> resource) override;
		void save(std::shared_ptr<CubA4::resources::IResource> resource) const override;
	private:
		void addKeyInBackwardsMap(const std::string &action, Button btn, BMods mods);
		void removeKeyInBackwardsMap(const std::string &action, Button btn, BMods mods);
	private:
		std::unordered_map<std::pair<Button, BMods>, std::vector<std::string>> keyMap_;
		std::unordered_multimap<std::string, std::pair<Button, BMods>> backKeyMap_;
		std::unordered_map<uint32_t, std::vector<std::string>> axisMap_;
	};
}
