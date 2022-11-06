#pragma once

#include <string>

namespace CubA4::info
{
	class IVersion
	{
	public:
		virtual unsigned short major() const = 0;
		virtual unsigned short minor() const = 0;
		virtual unsigned short patch() const = 0;
		
		virtual int build() const = 0;
		virtual int revision() const = 0;
		
		virtual std::string to_string() const = 0;
	protected:
		explicit IVersion() = default;
		virtual ~IVersion() = default;
	private:
	};
}
