#ifndef IMODBLOCKMANAGER_HPP
#define IMODBLOCKMANAGER_HPP

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

#endif // IMODBLOCKMANAGER_HPP
