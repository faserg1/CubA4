#pragma once

#include <info/IVersion.hpp>

namespace CubA4::info
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
