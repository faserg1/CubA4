#pragma once

#include <memory>
#include <util/ISubscription.hpp>

namespace CubA4::render::engine::pipeline
{
	class IRenderEntitySubscriber;
}

namespace CubA4::object
{
	class IEntityRenderManager
	{
	public:
		virtual std::unique_ptr<util::ISubscription> subscribe(CubA4::render::engine::pipeline::IRenderEntitySubscriber *subscriber) = 0;
	protected:
		explicit IEntityRenderManager() {}
		virtual ~IEntityRenderManager() {}
	};
}