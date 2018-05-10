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
		protected:
			explicit IModLoader() {}
		};
	}
}

#endif // IMODLOADER_HPP