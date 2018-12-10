#ifndef MODBASE_IMODITEMMANAGER_HPP
#define MODBASE_IMODITEMMANAGER_HPP

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

#endif // MODBASE_IMODITEMMANAGER_HPP
