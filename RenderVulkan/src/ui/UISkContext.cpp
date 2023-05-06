#include <ui/UISkContext.hpp>
using namespace CubA4::ui;

UISkContext::UISkContext(sk_sp<GrDirectContext> context) :
    context_(context)
{

}