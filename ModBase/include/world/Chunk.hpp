#ifndef CHUNK_HPP
#define CHUNK_HPP

namespace CubA4
{
	namespace world
	{
		class Chunk
		{
		public:
			virtual ~Chunk() {}
		protected:
			explicit Chunk() {}
		};
	}
}

#endif // CHUNK_HPP