#pragma once

#pragma once

#include <model/IRenderModelDefinition.hpp>
#include <memory>
#include <string>

namespace CubA4::manager
{
	class IModEntityManager
	{
	public:
		virtual ~IModEntityManager() = default;
	protected:
		explicit IModEntityManager() = default;
	private:
	};
}
