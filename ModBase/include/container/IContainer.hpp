#pragma once

namespace CubA4::container
{
	class IContainer
	{
	public:
		virtual ~IContainer() = default;
	protected:
		explicit IContainer() = default;
	};
}
