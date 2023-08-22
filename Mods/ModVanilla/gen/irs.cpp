#include "irs.hpp"
#include "irs-headers.hpp"
#include "irs-data.hpp"

#include <cstddef>

namespace CubA4
{
	namespace irs
	{
			const void *findFile(const char *name, std::size_t &size)
{
			const unsigned char *ptr = data;
			size = 0;
			auto iter = info.find(name);
			if (iter == info.end())
				return nullptr;
			size = iter->second.filesize;
			ptr += iter->second.offset;
			return ptr;
		}
	}
}

