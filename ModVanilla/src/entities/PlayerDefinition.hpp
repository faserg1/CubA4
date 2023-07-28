#pragma once

#include <entities/IPlayerDefinition.hpp>

namespace CubA4::object
{
	class PlayerDefinition : public virtual IPlayerDefinition
	{
	public:
		void onComponentStage(IEntityBuilder &builder) override;
		void onRenderPrepareStage(IEntityRenderBuilder &builder) override;
	};
}