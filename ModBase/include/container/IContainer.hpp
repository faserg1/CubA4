#ifndef ICONTAINER_HPP
#define ICONTAINER_HPP

namespace CubA4
{
	namespace container
	{
		class IContainer
		{
		public:
			virtual ~IContainer() = default;
		protected:
			explicit IContainer() = default;
		};
	}
}


#endif // ICONTAINER_HPP