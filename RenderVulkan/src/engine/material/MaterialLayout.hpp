#ifndef MATERIALLAYOUT_HPP
#define MATERIALLAYOUT_HPP

#include <memory>

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
				class MaterialLayout
				{
				public:
					explicit MaterialLayout(std::shared_ptr<vulkan::Pipeline> pipeline);
					~MaterialLayout();
				protected:
				private:
					const std::shared_ptr<vulkan::Pipeline> pipeline_;
				};
			}
		}
	}
}

#endif // MATERIALLAYOUT_HPP
