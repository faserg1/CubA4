#pragma once

#include "InstanceAddon.hpp"
#include <memory>

namespace CubA4::render::vulkan::addon
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
