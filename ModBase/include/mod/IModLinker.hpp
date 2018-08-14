#ifndef IMODLINKER_HPP
#define IMODLINKER_HPP

#include <memory>
#include <string>

namespace CubA4
{
	namespace mod
	{
		class IMod;

		class IModLinker
		{
		public:
			virtual std::shared_ptr<const IMod> getMod(std::string modId) = 0;
		protected:
			explicit IModLinker() = default;
			virtual ~IModLinker() = default;
		private:
		};
	}
}

#endif // IMODLINKER_HPP
