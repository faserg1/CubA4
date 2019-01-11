#ifndef CORE_RESOURCE_HPP
#define CORE_RESOURCE_HPP

#include <memory>
#include <boost/filesystem.hpp>
#include <resource/IResource.hpp>
#include "../filesystem/File.hpp"

namespace CubA4
{
	namespace core
	{
		namespace resources
		{
			class Resource :
				public virtual IResource, public filesystem::File
			{
			public:
				explicit Resource(boost::filesystem::path);
				~Resource();
			protected:
			private:
			};
		}
	}
}

#endif // CORE_RESOURCE_HPP
