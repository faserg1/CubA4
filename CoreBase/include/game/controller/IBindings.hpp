#pragma once

namespace CubA4
{
	namespace core
	{
		namespace game
		{
			namespace controller
			{
				class IBindings
				{
				public:
					virtual ~IBindings() = default;
				protected:
					explicit IBindings() = default;
				};
			}
		}
	}
}
