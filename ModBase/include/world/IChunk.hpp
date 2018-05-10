#ifndef ICHUNK_HPP
#define ICHUNK_HPP

namespace CubA4
{
	namespace world
	{
		class IChunk
		{
		public:
			virtual ~IChunk() {}
		protected:
			explicit IChunk() {}
		};
	}
}

#endif // ICHUNK_HPP