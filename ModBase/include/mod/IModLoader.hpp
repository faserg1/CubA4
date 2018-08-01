#ifndef IMODLOADER_HPP
#define IMODLOADER_HPP

#include <memory>

namespace CubA4
{
	namespace core
	{
		namespace system
		{
			class IEnvironmentBuilder;
		}
	}

	namespace mod
	{
		class IModLoader
		{
		public:
			virtual ~IModLoader() {}

			virtual void find() = 0;
			virtual void load() = 0;
			virtual void setup(std::shared_ptr<CubA4::core::system::IEnvironmentBuilder> builder) = 0;
			virtual void unload() = 0;
		protected:
			explicit IModLoader() {}
		};
	}
}

#endif // IMODLOADER_HPP