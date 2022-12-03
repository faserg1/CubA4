#pragma once

#include <memory>
#include <window/IWindow.hpp>
#include <vulkan/Surface.hpp>
#include "InstanceExtension.hpp"

namespace CubA4::render::vulkan::addon
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

		std::shared_ptr<Surface> createSurface() const;
	protected:
	private:
		std::weak_ptr<const Instance> instance_;
		std::shared_ptr<const window::IWindow> window_;
	};
}

