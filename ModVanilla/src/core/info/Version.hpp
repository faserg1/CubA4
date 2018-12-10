#ifndef MODVANILLA_VERSION_HPP
#define MODVANILLA_VERSION_HPP

#include <info/IVersion.hpp>

namespace CubA4
{
	namespace core
	{
		namespace info
		{
			class Version :
				public virtual IVersion
			{
			public:
				explicit Version(unsigned short major, unsigned short minor, unsigned short patch = 0, int build = 0, int rev = 0);
				explicit Version(const IVersion &version);
				~Version();

				unsigned short major() const override;
				unsigned short minor() const override;
				unsigned short patch() const override;

				int build() const override;
				int revision() const override;

				std::string to_string() const override;
			protected:
			private:
				const unsigned short major_;
				const unsigned short minor_;
				const unsigned short patch_;

				const int build_;
				const int revision_;
			};
		}
	}
}

#endif // MODVANILLA_VERSION_HPP
