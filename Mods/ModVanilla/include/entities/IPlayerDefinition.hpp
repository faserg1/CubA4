#pragma once

#include <object/IEntityDefinition.hpp>

namespace CubA4::object
{
	class IPlayerDefinition : public virtual IEntityDefinition
	{
	public:
		virtual ~IPlayerDefinition() = default;

	protected:
		IPlayerDefinition() = default;
	};
}