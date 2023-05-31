#include <ui/UISkContext.hpp>
using namespace CubA4::render::ui;

UISkContext::UISkContext(sk_sp<GrDirectContext> context) :
    context_(context)
{
	
}