#pragma once

#include <info/IVersion.hpp>

namespace CubA4::app
{
	class AppVersion :
		public virtual CubA4::info::IVersion
	{
	public:
		unsigned short major() const override;
		unsigned short minor() const override;
		unsigned short patch() const override;
		
		int build() const override;
		int revision() const override;
		
		std::string to_string() const override;
	protected:
	private:
	};
}
