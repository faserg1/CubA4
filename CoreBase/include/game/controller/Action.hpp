#pragma once

#include <string>

namespace CubA4::game::controller
{
    /// @brief An action with a context
    struct Action
    {
        /// Context of action. Empty, if not bound to the context
        std::string context;
        /// The action itself. Should not be empty
        std::string action;
    };
}