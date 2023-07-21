#pragma once

#include <object/IObject.hpp>

namespace CubA4::object
{
	class IEntity :
		public virtual IObject
	{
	public:
		virtual ~IEntity() = default;
	protected:
		explicit IEntity() = default;
	};
}
