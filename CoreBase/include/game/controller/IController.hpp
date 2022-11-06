#pragma once

namespace CubA4::game::controller
{
	class IController
	{
	public:
		virtual ~IController() = default;
	protected:
		explicit IController() = default;
	};
}
