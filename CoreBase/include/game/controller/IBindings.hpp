#pragma once

#include <string>
#include <vector>
#include <game/controller/Buttons.hpp>
#include <resources/IResource.hpp>

namespace CubA4::game::controller
{
	class IBindings
	{
	public:
		virtual ~IBindings() = default;

		// todo: ask for mod info?

		virtual void addKeyBinding(const std::string &action, Button btn, BMods mods) = 0;
		virtual void addAxisBinding(const std::string &action, AxisBinding axis) = 0;

		virtual void removeKeyBinding(const std::string &action, Button btn, BMods mods) = 0;
		virtual void removeAxisBinding(const std::string &action, AxisBinding axis) = 0;

		virtual const std::vector<std::string> *getKeyAction(Button btn, BMods mods) const = 0;
		virtual const std::vector<std::string> *getAxisAction(AxisBinding axis) const = 0;

		virtual void load(std::shared_ptr<const CubA4::resources::IResource> resource) = 0;
		virtual void save(std::shared_ptr<CubA4::resources::IResource> resource) const = 0;
	protected:
		explicit IBindings() = default;
	};
}
