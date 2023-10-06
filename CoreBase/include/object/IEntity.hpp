#pragma once

#include <core/IIdentityiMap.hpp>

namespace CubA4::object
{
	struct CameraComponent;

	class IEntity
	{
	public:
		using IdType = CubA4::core::IIdentityiMap::IdType;

		virtual ~IEntity() = default;
		virtual IdType getEntityId() const = 0;
		virtual IdType getFactoryId() const = 0;

		virtual CameraComponent *getCameraComponent() = 0;

		virtual void enableControls() = 0;
		virtual void disableControls() = 0;
		virtual bool isControlsEnabled() const = 0;
	protected:
		explicit IEntity() = default;
	};
}
