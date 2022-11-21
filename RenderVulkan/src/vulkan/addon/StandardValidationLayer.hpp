#pragma once

#include "InstanceLayer.hpp"

namespace CubA4::render::vulkan::addon
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

