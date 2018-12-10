#ifndef RENDERVULKAN_MATERIALLAYOUT_HPP
#define RENDERVULKAN_MATERIALLAYOUT_HPP

#include <memory>
#include <engine/material/IMaterialLayout.hpp>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Pipeline;
		}

		namespace engine
		{
			namespace material
			{
				class MaterialLayout :
					virtual public IMaterialLayout
				{
				public:
					explicit MaterialLayout(std::shared_ptr<vulkan::Pipeline> pipeline);
					~MaterialLayout();

					std::shared_ptr<vulkan::Pipeline> getPipeline() const;
				protected:
				private:
					const std::shared_ptr<vulkan::Pipeline> pipeline_;
				};
			}
		}
	}
}

#endif // RENDERVULKAN_MATERIALLAYOUT_HPP
