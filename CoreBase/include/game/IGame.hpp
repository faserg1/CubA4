#ifndef IGAME_HPP
#define IGAME_HPP

namespace CubA4
{
	namespace core
	{
		namespace game
		{
			class IGameSubscriber;

			class IGame
			{
			public:
				
			protected:
				explicit IGame() = default;
				virtual ~IGame() = default;
			private:
			};
		}
	}
}

#endif // IGAME_HPP
