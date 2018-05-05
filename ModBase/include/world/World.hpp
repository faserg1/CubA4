#ifndef WOLRD_HPP
#define WOLRD_HPP

#include <string>

namespace CubA4
{
	namespace world
	{
		class World
		{
		public:
			virtual ~World() {}

			virtual std::string getId() const = 0;
			virtual std::wstring getName() const = 0;
		protected:
			explicit World() {}
		};
	}
}

#endif // WOLRD_HPP