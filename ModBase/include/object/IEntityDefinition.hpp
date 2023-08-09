#pragma once

#include <object/IObject.hpp>

namespace CubA4::object
{
	class IEntityFactoryBuilder;
	class IEntityRenderBuilder;

	class IEntityDefinition : public virtual IObject
	{
	public:
		virtual ~IEntityDefinition() = default;

		virtual void onComponentStage(IEntityFactoryBuilder &builder) const = 0;
		virtual void onRenderPrepareStage(IEntityRenderBuilder &builder) const = 0;
	protected:
		explicit IEntityDefinition() = default;
	};
}
