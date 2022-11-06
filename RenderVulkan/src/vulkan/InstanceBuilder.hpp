#pragma once

#include <memory>
#include <string>
#include <vector>
#include <info/IApplicationInfo.hpp>

namespace CubA4
{
	namespace render
	{
		namespace vulkan
		{
			namespace addon
			{
				class InstanceLayer;
				class InstanceExtension;
			}

			class Instance;
			struct InstanceBuilderData;

			class InstanceBuilder
			{
			public:
				explicit InstanceBuilder(std::shared_ptr<const info::IApplicationInfo> info);
				~InstanceBuilder();

				void addLayer(addon::InstanceLayer &layer);
				void addExtension(addon::InstanceExtension &extension);
				std::shared_ptr<const Instance> build();
				void destroy(std::shared_ptr<const Instance> instance);
			protected:
			private:
				void fillAppInfo();

				std::shared_ptr<InstanceBuilderData> data_;
				std::shared_ptr<const info::IApplicationInfo> info_;
				std::vector<std::string> extensions_;
				std::vector<std::string> layers_;
			};
		}
	}
}
