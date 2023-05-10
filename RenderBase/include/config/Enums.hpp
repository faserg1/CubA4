#pragma once


namespace CubA4::render::config
{
    enum class AntiAliasing
    {
        Disabled = 0,
        MSAA2,
        MSAA4,
        MSAA8,
        MSAA16,
        MSAA32,
        MSAA64,
    };
}