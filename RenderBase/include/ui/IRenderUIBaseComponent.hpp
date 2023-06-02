#pragma once

namespace CubA4::render::ui
{
    class IRenderUIBaseComponent
    {
    public:
		virtual void setVisibility(bool visibility) = 0;
		virtual bool isVisible() const = 0;
		
		void show() {setVisibility(true);}
		void hide() {setVisibility(false);}
    protected:
        IRenderUIBaseComponent() = default;
        virtual ~IRenderUIBaseComponent() = default;
    };
}