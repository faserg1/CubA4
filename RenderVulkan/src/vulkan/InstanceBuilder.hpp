#ifndef INSTANCEBUILDER_HPP
#define INSTANCEBUILDER_HPP

#include <memory>
#include <string>
#include <vector>

namespace CubA4
{
	namespace core
	{
		namespace info
		{
			class IApplicationInfo;
		}
	}

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
				explicit InstanceBuilder(std::shared_ptr<const core::info::IApplicationInfo> info);
				~InstanceBuilder();

				void addLayer(addon::InstanceLayer &layer);
				void addExtension(addon::InstanceExtension &extension);
				std::shared_ptr<const Instance> build();
				void destroy(std::shared_ptr<const Instance> instance);
			protected:
			private:
				void fillAppInfo();

				std::shared_ptr<InstanceBuilderData> data_;
				std::shared_ptr<const core::info::IApplicationInfo> info_;
				std::vector<std::string> extensions_;
				std::vector<std::string> layers_;
			};
		}
	}
}

#endif // INSTANCEBUILDER_HPP 
