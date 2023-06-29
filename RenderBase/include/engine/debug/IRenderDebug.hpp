#pragma once

#include <memory>
#include <engine/debug/IRenderDebugCollection.hpp>

namespace CubA4::render::engine::debug
{
	class IRenderDebug
	{
	public:
		virtual ~IRenderDebug() = default;

		virtual [[nodiscard]] std::shared_ptr<IRenderDebugCollection> addCollection() = 0;
		virtual void setEnabled(bool enabled = true) = 0;
		virtual bool isEnabled() const = 0;
		void toggleEnabled() { setEnabled(!isEnabled()); }
	protected:
		IRenderDebug() = default;
	};
}