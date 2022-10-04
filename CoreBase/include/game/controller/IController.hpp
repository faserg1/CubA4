#pragma once

namespace CubA4
{
	namespace core
	{
		namespace game
		{
			namespace controller
			{
				class IController
				{
				public:
					virtual ~IController() = default;
				protected:
					explicit IController() = default;
				};
			}
		}
	}
}
