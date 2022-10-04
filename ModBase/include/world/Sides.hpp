#pragma once

namespace CubA4
{
	namespace mod
	{
		namespace world
		{
			/**
			 * @brief Стороны света
			 */
			enum class Side
			{
				North = 0,
				South = 1,
				East = 2,
				West = 3
			};

			/**
			 * @brief стороны блока
			 * 
			 */
			enum class BlockSide
			{
				Top = 1,
				Bottom = 2,
				Front = 3,
				Back = 4,
				Left = 5,
				Right = 6
			};
		}
	}
}
