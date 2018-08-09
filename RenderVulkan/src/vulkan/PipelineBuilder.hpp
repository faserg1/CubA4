#ifndef PIPELINEBUILDER_HPP
#define PIPELINEBUILDER_HPP

#include <memory>
#include <vulkan/vulkan.h>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			class Device;

			class PipelineBuilder
			{
			public:
				explicit PipelineBuilder(std::shared_ptr<const Device> device);
				~PipelineBuilder();
			protected:
			private:
				const std::shared_ptr<const Device> device_;
			};
		}
	}
}

#endif // PIPELINEBUILDER_HPP
