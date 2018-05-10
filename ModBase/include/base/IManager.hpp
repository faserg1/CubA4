#ifndef IMANAGER_HPP
#define IMANAGER_HPP

namespace CubA4
{
	namespace base
	{
		class IManager
		{
		public:
			virtual ~IManager() {}
		protected:
			explicit IManager() {}
		};
	}
}


#endif // IMANAGER_HPP