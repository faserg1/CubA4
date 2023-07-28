#pragma once

#include <memory>

namespace CubA4::object
{
	class IEntityFactoryBuilder
	{
	public:
		virtual ~IEntityFactoryBuilder() = default;
	protected:
		explicit IEntityFactoryBuilder() = default;
	};
}
