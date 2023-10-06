#pragma once

#include <object/IEntityDefinition.hpp>

namespace CubA4::object
{
	class ICubeEntityDefinition : public virtual IEntityDefinition
	{
	public:
		virtual ~ICubeEntityDefinition() = default;

	protected:
		ICubeEntityDefinition() = default;
	};
}