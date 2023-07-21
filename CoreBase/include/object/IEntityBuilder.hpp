#pragma once

namespace CubA4::object
{
	class IEntityBuilder
	{
	public:
		virtual ~IEntityBuilder() = default;

		/// @brief ???
		virtual void addComponent() = 0;
	protected:
		explicit IEntityBuilder() = default;
	};
}
