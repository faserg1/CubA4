#ifndef MODBASE_ICONTAINER_HPP
#define MODBASE_ICONTAINER_HPP

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


#endif // MODBASE_ICONTAINER_HPP