#pragma once

#include <skia/include/gpu/GrDirectContext.h>

namespace CubA4::ui
{
    class UISkContext
    {
    public:
        UISkContext(sk_sp<GrDirectContext> context);

        sk_sp<GrDirectContext> get() const { return context_; }
    private:
        sk_sp<GrDirectContext> context_;
    };
}