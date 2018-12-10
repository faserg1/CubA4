#ifndef RENDERVULKAN_SDLEXTENSION_HPP
#define RENDERVULKAN_SDLEXTENSION_HPP

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
				class SDLExtension :
					public InstanceExtension
				{
				public:
					explicit SDLExtension(std::shared_ptr<const window::IWindow> window);
					~SDLExtension();

					std::vector<std::string> names() const override;
					void init(std::shared_ptr<const Instance> instance) override;
					void destroy(std::shared_ptr<const Instance> instance) override;
					void added(InstanceBuilder &builder) override;

					std::shared_ptr<const Surface> getSurface() const;
				protected:
				private:
					std::shared_ptr<const window::IWindow> window_;
					std::shared_ptr<Surface> surface_;
				};
			}
		}
	}
}

#endif // RENDERVULKAN_SDLEXTENSION_HPP
