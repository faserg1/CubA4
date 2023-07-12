#pragma once

#include <memory>
#include <string>

namespace CubA4::mod
{
	class IMod;

	class IModLinker
	{
	public:
		virtual std::shared_ptr<const IMod> getMod(std::string modId) = 0;
	protected:
		explicit IModLinker() = default;
		virtual ~IModLinker() = default;
	private:
	};
}
