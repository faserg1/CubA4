#ifndef ICHUNK_HPP
#define ICHUNK_HPP

namespace CubA4
{
	namespace world
	{
		class IChunk
		{
		public:
			virtual ~IChunk() = default;
		protected:
			explicit IChunk() = default;
		};
	}
}

#endif // ICHUNK_HPP