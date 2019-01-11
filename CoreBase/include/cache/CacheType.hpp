#ifndef COREBASE_CACHETYPE_HPP
#define COREBASE_CACHETYPE_HPP

namespace CubA4
{
	namespace core
	{
		namespace cache
		{
			enum class CacheType
			{
				Core, ///< Кэш ядра
				Render, ///< Кэш рендер
				Mod, ///< Кэш модификаций
				Addon ///< Кэш дополнений (текстур паки?)
			};
		}
	}
}

#endif // COREBASE_CACHETYPE_HPP
