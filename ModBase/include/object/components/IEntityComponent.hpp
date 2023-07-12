#pragma once

namespace CubA4::object
{
	class IEntityComponent
	{
	public:
		virtual ~IEntityComponent() = default;
	protected:
		explicit IEntityComponent() = default;
	};
}
