#ifndef ICONTAINER_HPP
#define ICONTAINER_HPP

namespace CubA4
{
	namespace container
	{
		class IContainer
		{
		public:
			virtual ~IContainer() {}
		protected:
			explicit IContainer() {}
		};
	}
}


#endif // ICONTAINER_HPP