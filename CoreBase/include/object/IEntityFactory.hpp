#pragma once

#include <object/IObject.hpp>

namespace CubA4::object
{
	class IEntityFactory :
		public virtual IObject
	{
	public:
		virtual ~IEntityFactory() = default;
	protected:
		explicit IEntityFactory() = default;
	};
}
