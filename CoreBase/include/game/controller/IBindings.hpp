#pragma once

namespace CubA4::game::controller
{
	class IBindings
	{
	public:
		virtual ~IBindings() = default;
	protected:
		explicit IBindings() = default;
	};
}
