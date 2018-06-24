#ifndef VULKANADDON_HPP
#define VULKANADDON_HPP

#include <string>
#include <vector>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			namespace addon
			{
				enum class VulkanAddonType
				{
					Instance,
					Device
				};

				class VulkanAddon
				{
				public:
					virtual std::vector<std::string> names() const = 0;
					virtual VulkanAddonType type() const = 0;
					bool available() const;
				protected:
					explicit VulkanAddon();
					~VulkanAddon();

					virtual std::vector<std::string> allNames() const = 0;
				private:
				};
			}
		}
	}
}

#endif // VULKANADDON_HPP
