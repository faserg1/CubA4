#ifndef IMODITEMMANAGER_HPP
#define IMODITEMMANAGER_HPP

namespace CubA4
{
	namespace mod
	{
		namespace manager
		{
			class IModItemManager
			{
			public:
				virtual ~IModItemManager() = default;
			protected:
				explicit IModItemManager() = default;
			private:
			};
		}
	}
}

#endif // IMODITEMMANAGER_HPP
