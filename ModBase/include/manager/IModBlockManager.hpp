#ifndef MODBASE_IMODBLOCKMANAGER_HPP
#define MODBASE_IMODBLOCKMANAGER_HPP

namespace CubA4
{
	namespace mod
	{
		namespace manager
		{
			class IModBlockManager
			{
			public:
				virtual ~IModBlockManager() = default;
			protected:
				explicit IModBlockManager() = default;
			private:
			};
		}
	}
}

#endif // MODBASE_IMODBLOCKMANAGER_HPP
