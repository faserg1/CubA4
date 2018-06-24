#ifndef INSTANCELAYER_HPP
#define INSTANCELAYER_HPP

#include "InstanceAddon.hpp"
#include <memory>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			namespace addon
			{
				struct InstanceLayerData;

				class InstanceLayer :
					public InstanceAddon
				{
				public:
					explicit InstanceLayer();
					~InstanceLayer();
				protected:
					std::vector<std::string> allNames() const override;
				private:
					std::shared_ptr<InstanceLayerData> data_;
				};
			}
		}
	}
}

#endif // INSTANCELAYER_HPP
