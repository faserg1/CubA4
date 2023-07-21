#pragma once

#include <ui/IComponentFactory.hpp>
#include <ui/components/IMainCanvas.hpp>
#include <memory>

namespace CubA4::render::ui
{
    class IRenderUIManager
    {
	public:
		virtual std::shared_ptr<IComponentFactory> getComponentFactory() const = 0;
		virtual std::shared_ptr<IMainCanvas> getMainCanvas() const = 0;
    protected:
        IRenderUIManager() = default;
        virtual ~IRenderUIManager() = default;
    };
}