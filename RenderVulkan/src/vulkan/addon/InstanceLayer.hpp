#pragma once

#include "InstanceAddon.hpp"
#include <memory>

namespace CubA4::render::vulkan::addon
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
