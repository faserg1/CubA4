#pragma once

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <mod/IModLinker.hpp>


namespace CubA4::mod
{
	class ModLinker : public virtual IModLinker
	{
	public:
		ModLinker(std::vector<std::shared_ptr<IMod>> mods);
		~ModLinker();

		std::shared_ptr<const IMod> getMod(const std::string &modId) const override;
	private:
		std::unordered_map<std::string, std::shared_ptr<IMod>> mods_;
	};
}