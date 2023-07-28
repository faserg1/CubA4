#pragma once

namespace CubA4::object
{
	class IEntityRenderBuilder
	{
	public:
		virtual ~IEntityRenderBuilder() = default;

		/// @brief ???
		virtual void addModel() = 0;
	protected:
		explicit IEntityRenderBuilder() = default;
	};
}
