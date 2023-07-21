#pragma once

namespace CubA4::object
{
	class IEntityBuilder;

	class IEntityDefinition
	{
	public:
		virtual ~IEntityDefinition() = default;

		virtual void onComponentStage(IEntityBuilder &builder) = 0;
		virtual void onRenderPrepareStage(IEntityBuilder &builder) = 0;
	protected:
		explicit IEntityDefinition() = default;
	};
}
