#pragma once

#include <object/IEntityFactoryBuilder.hpp>

namespace CubA4::object
{
	struct EntityBuilderData;

	class EntityFactoryBuilder : public virtual IEntityFactoryBuilder
	{
	public:
		EntityFactoryBuilder(EntityBuilderData &data);
		void applyPhysicsDefinition(const CubA4::physics::IPhysicsEntityDefinition &def);
	private:
		EntityBuilderData &data_;
	};
}