#pragma once

#include <object/IEntity.hpp>

namespace CubA4::object
{
	class IItem :
		public virtual IEntity
	{
	public:
		virtual ~IItem() = default;
	protected:
		explicit IItem() = default;
	};
}
