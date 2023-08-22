#pragma once

#include <memory>
#include <string>

namespace CubA4::mod
{
	class IMod;

	class IModLinker
	{
	public:
		virtual std::shared_ptr<const IMod> getMod(const std::string &modId) const = 0;
	protected:
		IModLinker() = default;
		virtual ~IModLinker() = default;
	private:
	};
}
