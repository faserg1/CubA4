#pragma once

#include <ui/IUIManager.hpp>
#include <ui/UISkContext.hpp>

namespace CubA4::ui
{
    class UIManager
    {
    public:
        UIManager(UISkContext context);
    protected:
        UISkContext context_;
    };
}