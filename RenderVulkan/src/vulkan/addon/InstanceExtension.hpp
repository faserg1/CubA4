#ifndef INSTANCEEXTENSION_HPP
#define INSTANCEEXTENSION_HPP

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
				struct InstanceExtensionData;

				class InstanceExtension :
					public InstanceAddon
				{
				public:
					
					~InstanceExtension();
				protected:
					explicit InstanceExtension();
					std::vector<std::string> allNames() const override;
				private:
					std::shared_ptr<InstanceExtensionData> data_;
				};
			}
		}
	}
}

#endif // INSTANCEEXTENSION_HPP