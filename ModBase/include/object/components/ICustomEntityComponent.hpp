#pragma once

namespace CubA4::object
{
	class ICustomEntityComponent
	{
	public:
		virtual ~ICustomEntityComponent() = default;
	protected:
		explicit ICustomEntityComponent() = default;
	};
}
