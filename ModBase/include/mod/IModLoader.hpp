#ifndef IMODLOADER_HPP
#define IMODLOADER_HPP

namespace CubA4
{
	namespace mod
	{
		class IModLoader
		{
		public:
			virtual ~IModLoader() {}

			virtual void find() = 0;
			virtual void load() = 0;
			virtual void setup() = 0;
			virtual void unload() = 0;
		protected:
			explicit IModLoader() {}
		};
	}
}

#endif // IMODLOADER_HPP