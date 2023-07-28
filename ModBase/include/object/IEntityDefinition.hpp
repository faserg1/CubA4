#pragma once

#include <object/IObject.hpp>

namespace CubA4::object
{
	class IEntityBuilder;
	class IEntityRenderBuilder;

	class IEntityDefinition : public virtual IObject
	{
	public:
		virtual ~IEntityDefinition() = default;

		virtual void onComponentStage(IEntityBuilder &builder) = 0;
		virtual void onRenderPrepareStage(IEntityRenderBuilder &builder) = 0;
	protected:
		explicit IEntityDefinition() = default;
	};
}
