#ifndef SDLEXTENSION_HPP 
#define SDLEXTENSION_HPP 

#include <memory>
#include "InstanceExtension.hpp" 

namespace CubA4
{
	namespace window
	{
		class IWindow;
	}

	namespace render
	{
		namespace vulkan
		{
			class Surface; 

			namespace addon
			{
				class VSDLExtension : 
					public InstanceExtension 
				{
				public:
					explicit SDLExtension(std::shared_ptr<window::IWindow> window);
					~SDLExtension();

					std::vector<std::string> names() const override;
					void init(std::shared_ptr<const Instance> instance) override;
					void destroy(std::shared_ptr<const Instance> instance) override;
					void added(InstanceBuilder &builder) override;

					std::shared_ptr<const Surface> getSurface() const;
				protected:
				private:
					std::shared_ptr<window::IWindow> window_;
					std::shared_ptr<Surface> surface_;
				};
			}
		}
	}
}

#endif // SDLEXTENSION_HPP 
