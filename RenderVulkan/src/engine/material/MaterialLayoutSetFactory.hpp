#pragma once

#include <memory>
#include <engine/material/IMaterialLayoutSetFactory.hpp>
#include <vulkan/Device.hpp>
#include <vulkan/util/VulkanHandlerContainer.hpp>
#include <config/VulkanConfigAdapter.hpp>

namespace CubA4::render::engine
{
	class RenderPassManager;
	class ResourceManager;

	namespace material
	{
		class MaterialLayoutSetFactory :
			public virtual IMaterialLayoutSetFactory
		{
		public:
			explicit MaterialLayoutSetFactory(std::shared_ptr<const vulkan::Device> device,
				std::shared_ptr<const RenderPassManager> rpManager,
				std::shared_ptr<const ResourceManager> resourceManager,
				CubA4::render::config::VulkanConfigAdapter config);
			~MaterialLayoutSetFactory();

			std::shared_ptr<IMaterialLayoutBuilder> createMaterialLayout() override;
			std::vector<std::shared_ptr<const IMaterialLayout>> build() override;
		protected:
			
		private:
			const std::shared_ptr<const vulkan::Device> device_;
			const std::shared_ptr<const RenderPassManager> rpManager_;
			const std::shared_ptr<const ResourceManager> resourceManager_;
			const CubA4::render::config::VulkanConfigAdapter config_;
			std::vector<std::shared_ptr<IMaterialLayoutBuilder>> builders_;
		};
	}
}
