#ifndef RENDERVULKAN_STANDARTVALIDATIONLAYER_HPP
#define RENDERVULKAN_STANDARTVALIDATIONLAYER_HPP

#include "InstanceLayer.hpp"

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			namespace addon
			{
				class StandardValidationLayer :
					public InstanceLayer
				{
				public:
					explicit StandardValidationLayer();
					~StandardValidationLayer();

					std::vector<std::string> names() const override;
					void init(std::shared_ptr<const Instance> instance) override;
					void destroy(std::shared_ptr<const Instance> instance) override;
					void added(InstanceBuilder &builder) override;
				protected:
				private:
				};
			}
		}
	}
}

#endif // RENDERVULKAN_STANDARTVALIDATIONLAYER_HPP
