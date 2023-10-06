#pragma once

namespace CubA4::game::controller
{
	class IContextCallback
	{
	public:
		virtual void onContextChanged() = 0;
	};
}